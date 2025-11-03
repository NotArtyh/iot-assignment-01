#include "state/fsm.h"
#include "button/button.h"
#include "display/display.h"
#include "led/led.h"
#include <Arduino.h>

#define MAX_TIME_ST_INITAL 10000
#define MAX_TIME_ST_SLEEP 5000

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

/*
---------------------------------------------
FiniteStateMachine logic below
---------------------------------------------
*/

void fsm_init() { Serial.begin(9600); }

void handle_st_initial() {
    if (fsm_is_state_first_cycle()) {
    }

    green_led_off();
    status_led_pulse();
    display_print("Welcome to TOS!\nPress B1 to Start");

    if (state_elapsed_time > MAX_TIME_ST_INITAL) {
        fsm_transition_to(ST_SLEEP);
    }
}

void handle_st_sleep() {
    if (fsm_is_state_first_cycle()) {
        button_reset();
    }
    status_led_off();
    green_led_blink_sequence();
    display_print("Sleep mode zZz\nPress B1 to awake");

    if (button_is_pressed(1)) {
        fsm_transition_to(ST_INITIAL);
    }
}

void handle_st_setup() {}

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
    default:
        break;
    }
}