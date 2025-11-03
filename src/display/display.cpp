#include "display/display.h"

#ifdef USE_OLED
#include "display/oled_display.h"

void display_init() { oled_init(); }
void display_print(const char *text) { oled_print(text); }
void display_test_print() { oled_test_print(); }

#else
#include "display/lcd_display.h"

void display_init() { lcd_init(); }
void display_print(const char *text, uint8_t row, uint8_t col) {
    lcd_print(text, row, col);
}
void display_test_print() { lcd_test_print(); }

#endif
