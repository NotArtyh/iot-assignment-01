#include "display/oled_display.h"
#include "config.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include <string.h>

U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE, I2C_DATA, I2C_CLK);

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
    for (int i = 0; i <= size; i++) {
        if (text[i] == '\n' || text[i] == '\0') {
            strncpy(buffer, text + j, i - j);
            buffer[i - j] = '\0';
            u8x8.drawString(0, y, buffer);
            y++;
            j = i + 1;
        };
    }
}