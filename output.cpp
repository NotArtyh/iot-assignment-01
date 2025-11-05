#include "config.h"
#include "output.h"
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "setupIO.h"

// FADING LED VARIABLES
int fadeAmount = 5;
int currIntensity = 0;

// FUNZIONI SUI LED

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void pulseLs()
{
    analogWrite(LS, currIntensity);
    currIntensity = currIntensity + fadeAmount;
    if (currIntensity == 0 || currIntensity == 255)
    {
        fadeAmount = -fadeAmount;
    }
    delay(20);
}

void greenLedsOff()
{
    for (int i = 0; i < NUM_GREEN_LEDS; i++)
        digitalWrite(greenLeds[i], LOW);
}

void displayMessage(Msg message)
{
    switch (message)
    {
    case MSG_WELCOME:
        Serial.println("Welcome to TOS! Push B1 to Start");    // DEBUGGING
        display.clearDisplay();                              // Pulisce lo schermo
        display.setTextSize(2);                                  // Testo 2x
        display.setTextColor(SH110X_WHITE);                      // Testo bianco
        display.setCursor(20, 25);                               // Posizione del testo (x, y)
        display.println(F("Welcome to TOS! Press B1 to Start")); // Scrive il testo
        display.display();
        break;
    default:
        break;
    }
}
