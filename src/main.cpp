#include "io.h"
#include "state/fsm.h"
#include <Arduino.h>

void setup() {
    fsm_init();
    input_init();
    output_init();
}

void loop() { fsm_update(); }