#include <config.h>
#include <core.h>
#include <io.h>
#include <kernel.h>

#include <Arduino.h>

// implementation of state logic



void handleInitialState() {
    displayMessage("Welcome to TOS! Press B1 to Start");
}

void handleSleepState() {}

void handleSetupState() {}