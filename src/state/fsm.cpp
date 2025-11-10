#include "state/fsm.h"
#include "button/button.h"
#include "display/display.h"
#include "game/game.h"
#include "led/led.h"
#include <Arduino.h>

#define MAX_TIME_ST_INITAL 10000
#define MAX_TIME_ST_SLEEP 5000
#define MAX_TIME_ST_SETUP 2000
#define MAX_TIME_ST_LOSE 10000
#define MAX_TIME_ST_WIN 5000
#define MAX_TIME_ST_ROUND 30000
#define ST_ROUND_STEP 1000

long time_st_round = MAX_TIME_ST_ROUND;

state_t state_current = ST_INITIAL;
bool state_first_cycle = true;
long state_entry_time;
long state_elapsed_time;

bool fsm_is_state_first_cycle() {
    bool com = state_first_cycle;
    state_first_cycle = false;
    return com;
}

void fsm_transition_to(state_t state_new) {
    state_current = state_new;
    state_entry_time = millis();
    state_first_cycle = true;
}

void fsm_update_state_time() {
    state_elapsed_time = millis() - state_entry_time;
}

void fsm_update_round_time() { time_st_round -= ST_ROUND_STEP; }
void fsm_reset_round_time() { time_st_round = MAX_TIME_ST_ROUND; }

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

void fsm_init() {
    Serial.begin(9600);
    Serial.println(freeRam());
}

void handle_st_initial() {
    if (fsm_is_state_first_cycle()) {
        green_led_off();
        display_print_P(MSG_INITIAL);
    }

    status_led_pulse();

    if (state_elapsed_time > MAX_TIME_ST_INITAL) {
        fsm_transition_to(ST_SLEEP);
    }

    if (button_is_pressed(1)) {
        fsm_transition_to(ST_SETUP);
    }
}

void handle_st_sleep() {
    if (fsm_is_state_first_cycle()) {
        button_reset();
        display_print_P(MSG_SLEEP);
    }
    status_led_off();
    green_led_blink_sequence();

    if (button_is_pressed(1)) {
        fsm_transition_to(ST_INITIAL);
    }
}

void handle_st_setup() {
    if (fsm_is_state_first_cycle()) {
        game_reset();
        green_led_off();
        status_led_off();
        fsm_reset_round_time();
        display_print_P(MSG_SETUP);
    }

    if (state_elapsed_time > MAX_TIME_ST_SETUP) {
        fsm_transition_to(ST_ROUND);
    };
}

void handle_st_round() {
    if (fsm_is_state_first_cycle()) {
        button_reset();
        game_shuffle_sequence();
        display_print(game_get_sequence_string());
    }

    // move to a proper place + mehtod
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
        green_led_off();
        display_print_P(MSG_LOSE);
    }

    if (state_elapsed_time < 2000) {
        status_led_on();
    } else {
        status_led_off();
    }

    if (state_elapsed_time > MAX_TIME_ST_LOSE) {
        fsm_transition_to(ST_INITIAL);
    };
}

void handle_st_win() {
    if (fsm_is_state_first_cycle()) {
        green_led_off();
        game_update_score();
        display_print_P(MSG_WIN);
        delay(1000);
        char str_score[24];
        sprintf(str_score, "Score: %d", game_get_score());
        display_print(str_score);
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