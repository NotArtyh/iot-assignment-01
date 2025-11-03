#include "display/oled_display.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#define i2c_Address 0x3c

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SH1106G display =
    Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void oled_init() {
    delay(250);
    display.begin(i2c_Address, true);
    display.display();
    delay(2000);
    display.clearDisplay();

    display.setTextSize(2);
    display.setTextColor(SH110X_WHITE);
}

void oled_test_print() {
    display.setCursor(0, 0);
    display.println("Test 123");
    display.display();
}

void oled_print(const char *text) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(text);
    display.display();
}