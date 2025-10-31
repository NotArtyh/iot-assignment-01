#include "config.h"
#include "output.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h> //non so se sia necessario per le funzioni lc

// FADING LED VARIABLES
int fadeAmount;
int currIntensity;
currIntensity = 0;
fadeAmount = 5;

// FUNZIONI SUI LED

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
        Serial.println("Welcome to TOS! Push B1 to Start") // DEBUGGING
            lcd.setCursor(1, 0);
        lcd.print("Welcome to TOS!");
        lcd.setCursor(0, 1);
        lcd.print("Push B1 to Start");
        break;
    case:
        break;
    default:
        break;
    }
}
