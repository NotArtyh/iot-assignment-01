#include "state/fsm.h"
#include "button/button.h"
#include "display/display.h"
#include "game/game.h"
#include "led/led.h"
#include <Arduino.h>

#define MAX_TIME_ST_INITAL 10000
#define MAX_TIME_ST_SLEEP 5000
#define ST_ROUND_STEP 1000

long max_time_st_round = 30000;

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

void fsm_update_round_time() { max_time_st_round -= ST_ROUND_STEP; }

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
        Serial.println(freeRam());
        // display_print("Welcome to TOS!\nPress B1 to Start");
        display_print_static(MSG_INITIAL);
    }

    status_led_pulse();

    if (state_elapsed_time > MAX_TIME_ST_INITAL) {
        fsm_transition_to(ST_ROUND);
    }
}

void handle_st_sleep() {
    if (fsm_is_state_first_cycle()) {
        button_reset();
        Serial.println(freeRam());
        // display_print("Sleep mode zZz\nPress B1 to awake");
        display_print_static(MSG_SLEEP);
    }
    status_led_off();
    green_led_blink_sequence();

    if (button_is_pressed(1)) {
        fsm_transition_to(ST_INITIAL);
    }
}

void handle_st_setup() {}

void handle_st_round() {
    if (fsm_is_state_first_cycle()) {
        button_reset();
        fsm_update_round_time();
        game_shuffle_sequence();
        Serial.println(freeRam());
        display_print(game_get_sequence_string());
        // Serial.println(game_get_sequence_string());
    }

    for (size_t i = 0; i < 4; i++) {
        if (button_is_pressed(i)) {
            green_led_on_index(i);
        }
    }
    // Serial.println(button_get_current_pressed());
    // if (state_elapsed_time % 2000 == 0) {
    //     Serial.println(game_get_user_sequence_index());
    // }

    // lose condition | elapsed time || wrong sequnce order
    // if (state_elapsed_time > max_time_st_round ||
    //     !game_is_validate_sequence()) {
    //     fsm_transition_to(ST_SLEEP);
    // }
    // Serial.println(button_get_last_pressed());
    // if (game_matched_sequence()) {
    //     fsm_transition_to(ST_INITIAL);
    // }
    if (state_elapsed_time > max_time_st_round ||
        (game_is_match_started() && !game_is_current_valid())) {
        // Serial.println("you lost");
        fsm_transition_to(ST_LOSE);
    }

    if (game_is_match_started() && game_all_match()) {
        // Serial.println("you won");
        fsm_transition_to(ST_INITIAL);
    }
}

void handle_st_lose() {
    if (fsm_is_state_first_cycle()) {
        display_print_static(MSG_LOSE);
    }
}

void handle_st_win() {}

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