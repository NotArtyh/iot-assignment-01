#include "button/button.h"
#include "config.h"
#include <Arduino.h>
#include <EnableInterrupt.h>

#define BOUNCING_TIME 50

uint8_t button[] = {BTN1, BTN2, BTN3, BTN4};

bool button_pressed[NUM_BUTTONS] = {false, false, false, false};
unsigned long button_pressed_timestamp[NUM_BUTTONS] = {0, 0, 0, 0};
int button_current_pressed = 0;

// button wrapper to allow for debounce with enableInterrupt
void button_handler(int i);
void button_handler0() { button_handler(0); }
void button_handler1() { button_handler(1); }
void button_handler2() { button_handler(2); }
void button_handler3() { button_handler(3); }
void (*button_handlers[NUM_BUTTONS])() = {button_handler0, button_handler1,
                                          button_handler2, button_handler3};

void button_handler(int i) {
    unsigned long ts = millis();
    if (ts - button_pressed_timestamp[i] > BOUNCING_TIME) {
        button_pressed_timestamp[i] = ts;
        int status = digitalRead(button[i]);
        if (status == HIGH && !button_pressed[i]) {
            button_pressed[i] = true;
            button_current_pressed++;
        }
    }
}

void button_init() {
    for (int i = 0; i < NUM_BUTTONS; i++) {
        pinMode(button[i], INPUT);
        enableInterrupt(button[i], button_handlers[i], RISING);
    }
}

void button_reset() {
    unsigned long ts = millis();
    for (int i = 0; i < NUM_BUTTONS; i++) {
        button_pressed[i] = false;
        button_pressed_timestamp[i] = ts;
    }
    button_current_pressed = 0;
}

bool button_is_pressed(int index) { return button_pressed[index]; }

int button_get_current_pressed() { return button_current_pressed; }