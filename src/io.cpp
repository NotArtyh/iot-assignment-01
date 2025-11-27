#include "io.h"
#include "button/button.h"
#include "display/display.h"
#include "led/led.h"
#include "potentiometer/potentiometer.h"

void input_init() {
    button_init();
    pot_init();
}

void output_init() {
    led_init();
    display_init();
}