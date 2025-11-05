#include "config.h"
#include "input.h"
#include "setupIO.h"
#include <Arduino.h>
#include <EnableInterrupt.h>

// input output logic, handles display for now


bool buttonPressed[NUM_BUTTONS] = {false, false, false, false};

long lastButtonPressedTimestamps[NUM_BUTTONS];

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
    int status = digitalRead(inputButtons[i]);
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
    pinMode(inputButtons[i], INPUT);
    enableInterrupt(inputButtons[i], buttonHandlers[i], CHANGE);
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
