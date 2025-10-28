#include "config.h"
#include "input.h"
#include <Arduino.h>
#include <EnableInterrupt.h>

// input output logic, handles display for now

int greenLeds[] = {L1, L2, L3, L4};
int inputButtons[] = {B1, B2, B3, B4};
bool buttonPressed[NUM_BUTTONS] = {false, false, false, false};

long lastButtonPressedTimestamps[NUM_BUTTONS];

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

void buttonHandler(int i);
void buttonHandler0() { buttonHandler(0); }
void buttonHandler1() { buttonHandler(1); }
void buttonHandler2() { buttonHandler(2); }
void buttonHandler3() { buttonHandler(3); }

void (*buttonHandlers[NUM_BUTTONS])() = {buttonHandler0, buttonHandler1, buttonHandler2, buttonHandler3};

void buttonHandler(int i)
{
  long ts = millis();
  if (ts - lastButtonPressedTimestamps[i] > BOUNCING_TIME)
  {
    lastButtonPressedTimestamps[i] = ts;
    int status = digitalRead(inputPins[i]);
    if (status == HIGH && !buttonPressed[i])
    {
      buttonPressed[i] = true;
    }
  }
}

void initInput()
{
  for (int i = 0; i < NUM_BUTTONS; i++)
  {
    pinMode(inputPins[i], INPUT);
    enableInterrupt(inputPins[i], buttonHandlers[i], CHANGE);
  }
}

void resetInput()
{
  long ts = millis();
  for (int i = 0; i < NUM_BUTTONS; i++)
  {
    buttonPressed[i] = false;
    lastButtonPressedTimestamps[i] = ts;
  }
}

bool isButtonPressed(int buttonIndex)
{
  return buttonPressed[buttonIndex];
}

bool hasBeenPressed(int index)
{
  return buttonPressed[index];
}
