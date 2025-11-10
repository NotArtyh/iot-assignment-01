#include "display/display.h"
#include <avr/pgmspace.h>

const char msg_initial[] PROGMEM = "Welcome to TOS!\nPress B1\nto Start";
const char msg_sleep[] PROGMEM = "Sleep mode zZz\nPress B1 to awake";
const char msg_setup[] PROGMEM = "Go!";
const char msg_lose[] PROGMEM = "Game Over";
const char msg_win[] PROGMEM = "GOOD!";

const char *const display_messages[] PROGMEM = {msg_initial, msg_sleep,
                                                msg_setup, msg_lose, msg_win};

#ifdef USE_OLED
#include "display/oled_display.h"

void display_init() { oled_init(); }
void display_print(const char *text) { oled_print(text); }
void display_test_print() { oled_test_print(); }
void display_print_P(message msg) { oled_print_P(display_messages[msg]); }

#else
#include "display/lcd_display.h"

void display_init() { lcd_init(); }
void display_print(const char *text, uint8_t row, uint8_t col) {
    lcd_print(text, row, col);
}
void display_print_P(message msg) { lcd_print_P(display_messages[msg]); };
void display_test_print() { lcd_test_print(); }

#endif
