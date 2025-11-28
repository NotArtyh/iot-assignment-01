#include "display/display.h"
#include <Arduino.h>
#include <avr/pgmspace.h>

const char msg_initial[] PROGMEM = "Welcome to TOS!\nPress B1\nto Start";
const char msg_sleep[] PROGMEM = "Sleep mode zZz\nPress B1\nto awake";
const char msg_setup[] PROGMEM = "Go!\nTurn pot for\ndifficulty";
const char msg_lose[] PROGMEM = "Game Over\nScore: %d";
const char msg_win[] PROGMEM = "GOOD!\nScore: %d";

const char *const display_messages[] PROGMEM = {msg_initial, msg_sleep,
                                                msg_setup, msg_lose, msg_win};

void display_print_P(message msg, ...) {
    const char *text = (const char *)pgm_read_word(&display_messages[msg]);
    char buffer[64];
    va_list args;
    va_start(args, msg);
    vsprintf_P(buffer, text, args);
    display_print(buffer);
}

#ifdef USE_OLED
#include "display/oled_display.h"

void display_init() { oled_init(); }
void display_print(const char *text) { oled_print(text); }
void display_test_print() { oled_test_print(); }

#else
#include "display/lcd_display.h"

void display_init() { lcd_init(); }
void display_print(const char *text) { lcd_print(text); }
void display_test_print() { lcd_test_print(); }

#endif
