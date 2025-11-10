#include "display/oled_display.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include <string.h>

U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE, A5, A4);

void oled_init() {
    u8x8.begin();
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    delay(100);
}

void oled_test_print() {
    u8x8.setCursor(0, 0);
    u8x8.print("Test 123");
    u8x8.display();
}

void oled_print(const char *text) {
    u8x8.clear();
    int size = strlen(text);
    int y = 0;
    int j = 0;
    char buffer[size];
    buffer[0] = '\0';
    for (size_t i = 0; i <= size; i++) {
        if (text[i] == '\n' || text[i] == '\0') {
            strncpy(buffer, text + j, i - j);
            buffer[i - j] = '\0';
            u8x8.drawString(0, y, buffer);
            y++;
            j = i + 1;
        };
    }
}

void oled_print_static(const char *text) {
    char buffer[strlen(text) + 1];
    strncpy_P(buffer, text, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    oled_print(buffer);
}