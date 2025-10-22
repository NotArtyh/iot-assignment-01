#include <config.h>
#include <io.h>

#include <Arduino.h>
#include <EnableInterrupt.h>

// input output logic, handles display for now

unit8_t outputPins[] = {L1, L2, L3, L4, LS};
unit8_t inputPins[] = {B1, B2, B3, B4};

void initInput() {
    for (int i = 0; i < NUM_BUTTONS; i++) {
        pinMode(inputPins[i], INPUT);
        enableInterrupt(inputPins[i], buttonHandlers[i], CHANGE);
    }
}

// FADING LED VARIABLES
int fadeAmount;
int currIntensity;
// LS SETUP
currIntensity = 0;
fadeAmount = 5;


void fade_led(unit8_t ledPin) {
    analogWrite(LS, currIntensity);
    currIntensity = currIntensity + fadeAmount;
    if (currIntensity == 0 || currIntensity == 255) {
        fadeAmount = -fadeAmount;
    }
    delay(20);
}

void displayMessage(char message[]) {}