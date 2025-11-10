#include "display/lcd_display.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

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
    // add support for line splitting like oled
}

void lcd_print_static(const char *text) {
    char buffer[strlen(text) + 1];
    strncpy_P(buffer, text, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    lcd_print(buffer);
}