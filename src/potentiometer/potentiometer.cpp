#include "config.h"
#include <Arduino.h>

int factor = 1;

void pot_init() { pinMode(POT, INPUT); }

void pot_update_factor() {
    int potValue = analogRead(POT);
    factor = map(potValue, 0, 1023, 1, 4);
}

int pot_get_factor() { return factor; }