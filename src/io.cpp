#include <Arduino.h>
#include <EnableInterrupt.h>
#include <config.h>
#include <io.h>

int currIntensity = 0;
int fadeAmount = 5;

unit8_t outputPins[] = {L1, L2, L3, L4, LS};
unit8_t inputPins[] = {B1, B2, B3, B4};

void initInput() {
    for (int i = 0; i < NUM_BUTTONS; i++) {
        pinMode(inputPins[i], INPUT);
        enableInterrupt(inputPins[i], buttonHandlers[i], CHANGE);
    }
}

void initOutput() {
    for (int i = 0; i < NUM_LEDS; i++) {
        pinMode(outputPins[i], OUTPUT);
    }
}

void fadeLed(unit8_t ledPin) {
    analogWrite(ledPin, currIntensity);
    currIntensity = currIntensity + fadeAmount;
    if (currIntensity == 0 || currIntensity == 255) {
        fadeAmount = -fadeAmount;
    }
    delay(20);
}

void displayMessage(char message[]) {}