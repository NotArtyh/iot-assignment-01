#include "core.h"
#include "input.h"
#include "output.h"
#include "kernel.h"
#include <Arduino.h>

// implementation of state logic

void initCore()
{ // funzione utile per il debugging
    Serial.begin(9600);
}

void handleInitialState()
{
    greenLedsOff();
    pulseLs();
    displayMessage(MSG_WELCOME);
}

void handleSleepState() {}

void handleSetupState() {}