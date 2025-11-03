#include "config.h"
#include <Arduino.h>

uint8_t greenLeds[] = {L1, L2, L3, L4};

int fadeAmount = 20;
int currIntensity = 0;

void green_led_init() {
    for (size_t i = 0; i < NUM_GREEN_LEDS; i++) {
        pinMode(greenLeds[i], OUTPUT);
    }
}

void status_led_init() { pinMode(LS, OUTPUT); }

void led_init() {
    green_led_init();
    status_led_init();
}

void status_led_pulse() {
    analogWrite(LS, currIntensity);
    currIntensity = currIntensity + fadeAmount;
    if (currIntensity == 0 || currIntensity == 255) {
        fadeAmount = -fadeAmount;
    }
    delay(20);
}

void status_led_off() { digitalWrite(LS, LOW); }

void green_led_off() {
    for (int i = 0; i < NUM_GREEN_LEDS; i++)
        digitalWrite(greenLeds[i], LOW);
}

void green_led_on() {
    for (int i = 0; i < NUM_GREEN_LEDS; i++)
        digitalWrite(greenLeds[i], HIGH);
}

int blink_counter = 0;
void green_led_blink_sequence() {
    green_led_off();
    digitalWrite(greenLeds[blink_counter], HIGH);
    delay(100);
    blink_counter = (blink_counter + 1) % NUM_GREEN_LEDS;
}
