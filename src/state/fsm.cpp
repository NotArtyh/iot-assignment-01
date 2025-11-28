#include "state/fsm.h"
#include "avr/sleep.h"
#include "button/button.h"
#include "display/display.h"
#include "game/game.h"
#include "led/led.h"
#include "potentiometer/potentiometer.h"
#include <Arduino.h>

#define MAX_TIME_ST_INITAL 10000
#define MAX_TIME_ST_SLEEP 5000
#define MAX_TIME_ST_SETUP 10000
#define MAX_TIME_ST_LOSE 10000
#define MAX_TIME_ST_LOSE_STATUS_ON 2000
#define MAX_TIME_ST_WIN 5000
#define MAX_TIME_ST_ROUND 30000
#define ST_ROUND_STEP 1000

long time_st_round = MAX_TIME_ST_ROUND;

state_t state_current = ST_INITIAL;
bool state_first_cycle = true;
long state_entry_time;
long state_elapsed_time;
static int difficulty;

bool fsm_is_state_first_cycle() {
    bool com = state_first_cycle;
    state_first_cycle = false;
    return com;
}

void fsm_transition_to(state_t state_new) {
    state_current = state_new;
    state_entry_time = millis();
    state_first_cycle = true;
    button_reset();
    green_led_off();
    status_led_off();
}

void fsm_update_state_time() {
    state_elapsed_time = millis() - state_entry_time;
}

void fsm_update_round_time() { time_st_round -= ST_ROUND_STEP * difficulty; }
void fsm_reset_round_time() { time_st_round = MAX_TIME_ST_ROUND; }

void fsm_update_difficulty() {
    pot_update_factor();
    difficulty = pot_get_factor();
};

// Debugging | gets the current ammount of ram available, used with serialprint
int freeRam() {
    extern int __heap_start, *__brkval;
    int v;
    return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

/*
---------------------------------------------
FiniteStateMachine logic below
---------------------------------------------
*/

void fsm_init() { Serial.begin(9600); }

void handle_st_initial() {
    if (fsm_is_state_first_cycle()) {
        display_print_P(MSG_INITIAL);
    }

    status_led_pulse();

    if (state_elapsed_time > MAX_TIME_ST_INITAL) {
        fsm_transition_to(ST_SLEEP);
    }

    if (button_is_pressed(0)) {
        fsm_transition_to(ST_SETUP);
    }
}

void handle_st_sleep() {
    if (fsm_is_state_first_cycle()) {
        display_print_P(MSG_SLEEP);
    }

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();

    fsm_transition_to(ST_INITIAL);
}

void handle_st_setup() {
    if (fsm_is_state_first_cycle()) {
        game_reset();
        fsm_reset_round_time();
        display_print_P(MSG_SETUP);
    }
    
    fsm_update_difficulty();
    green_led_off();
    green_led_on_index(difficulty - 1);

    if (state_elapsed_time > MAX_TIME_ST_SETUP) {
        fsm_transition_to(ST_ROUND);
    };
}

void handle_st_round() {
    if (fsm_is_state_first_cycle()) {
        game_shuffle_sequence();
        display_print(game_get_sequence_string());
        Serial.println(time_st_round); // debugging
    }

    for (size_t i = 0; i < 4; i++) {
        if (button_is_pressed(i)) {
            green_led_on_index(i);
        }
    }

    if (state_elapsed_time > time_st_round ||
        (game_is_match_started() && !game_is_current_valid())) {
        fsm_transition_to(ST_LOSE);
    }

    if (game_is_match_started() && game_all_match()) {
        fsm_transition_to(ST_WIN);
    }
}

void handle_st_lose() {
    if (fsm_is_state_first_cycle()) {
        status_led_on();
        display_print_P(MSG_LOSE, game_get_score());
    }

    if (state_elapsed_time > MAX_TIME_ST_LOSE_STATUS_ON) {
        status_led_off();
    }

    if (state_elapsed_time > MAX_TIME_ST_LOSE) {
        fsm_transition_to(ST_INITIAL);
    };
}

void handle_st_win() {
    if (fsm_is_state_first_cycle()) {
        game_update_score();
        display_print_P(MSG_WIN, game_get_score());
        fsm_update_round_time();
    }

    if (state_elapsed_time > MAX_TIME_ST_WIN) {
        fsm_transition_to(ST_ROUND);
    };
}

void fsm_update() {
    fsm_update_state_time();
    switch (state_current) {
    case ST_INITIAL:
        handle_st_initial();
        break;
    case ST_SLEEP:
        handle_st_sleep();
        break;
    case ST_SETUP:
        handle_st_setup();
        break;
    case ST_ROUND:
        handle_st_round();
        break;
    case ST_LOSE:
        handle_st_lose();
        break;
    case ST_WIN:
        handle_st_win();
        break;
    default:
        break;
    }
}