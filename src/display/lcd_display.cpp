#include "display/lcd_display.h"
#include "config.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

void lcd_init() {
    lcd.init();
    lcd.backlight();
}

void lcd_test_print() {
    lcd.setCursor(3, 0);
    lcd.print("Test 123");
}

// void displayMessage(Msg message) {
//     switch (message) {
//     case MSG_WELCOME:
//         Serial.println("Welcome to TOS! Push B1 to Start"); // DEBUGGING
//         lcd.setCursor(1, 0);
//         lcd.print("Welcome to TOS!");
//         lcd.setCursor(0, 1);
//         lcd.print("Push B1 to Start");
//         break;
//     default:
//         break;
//     }
// }

void lcd_print(const char *text) {
    lcd.clear();
    int size = strlen(text);
    int y = 0;
    int j = 0;
    char buffer[size];
    buffer[0] = '\0';
    for (int i = 0; i <= size; i++) {
        if (text[i] == '\n' || text[i] == '\0') {
            strncpy(buffer, text + j, i - j);
            buffer[i - j] = '\0';
            lcd.setCursor(0, y);
            lcd.print(buffer);
            y++;
            j = i + 1;
        };
    }
}
