/****************************************************************************/
/*
Course: IoT Embedded Systems
Year: 2025/2026
Title: assignment-01
Authors:
    - Muller Arthur Istvan
        Matricola: 0001145303
    - Cattolico Giuseppe
        Matricola: 0001124318
*/
/****************************************************************************/

#include "io.h"
#include "state/fsm.h"
#include <Arduino.h>

void setup() {
    fsm_init();
    input_init();
    output_init();
}

void loop() { fsm_update(); }