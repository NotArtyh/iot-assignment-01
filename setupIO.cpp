#include "config.h"
#include "setupIO.h"
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>


Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// SETUP DEI LED, BUTTONS E DISPLAY

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
  display.begin(i2c_Address, true);
  // Mostra splash screen iniziale Adafruit per 2 secondi
  display.display();
  delay(2000);

  // Cancella tutto il buffer
  display.clearDisplay();
}

void setupIO()
{
  setupGreenLeds();
  setupLs();
  setupButtons();
  setupDisplay();
}
