#include "config.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// initialize display

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

// SETUP DEI LED, BUTTONS E DISPLAY (spostare tutto il setup altrove intanto lo lascio qui)

void setupGreenLeds()
{
  for (int i = 0; i < NUM_GREEN_LEDS; i++)
  {
    pinMode(greenLeds[i], OUTPUT);
  }
}

void setupLs()
{
  pinMode(LS, OUTPUT);
}

void setupButtons()
{
  for (int i = 0; i < NUM_BUTTONS; i++)
  {
    pinMode(inputButtons[i], INPUT);
  }
}

void setupDisplay()
{
  lcd.init();
  lcd.backlight();
}

void setupIO()
{
  setupGreenLeds();
  setupLs();
  setupButtons();
  setupDisplay();
}