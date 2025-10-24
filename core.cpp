#include "core.h"
#include "io.h"
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
    displayMessage("Welcome to TOS! Press B1 to Start");
}

void handleSleepState() {}

void handleSetupState() {}