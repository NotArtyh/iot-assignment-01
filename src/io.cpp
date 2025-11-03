#include "io.h"
#include "button/button.h"
#include "display/display.h"
#include "led/led.h"

void input_init() { button_init(); }

void output_init() {
    led_init();
    display_init();
}