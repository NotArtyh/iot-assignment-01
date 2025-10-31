#include "kernel.h"

// helper functions to core

State currentState;

/* time in which the game entered in current state */
long enteredStateTime;

/* how long it the game is in current state */
long currentTimeInState;

/* flag which is true if it is the first cycle in that state */
bool firstCheckInState;

State getCurrentState() { return currentState; }

long getCurrentTimeInState()
{
  return currentTimeInState;
}

long getEnteredStateTime()
{
  return enteredStateTime;
}

bool isJustEnteredInState()
{
  bool com = firstCheckInState;
  firstCheckInState = false;
  return com;
}

void changeState(State newState)
{
  currentState = newState;
  enteredStateTime = millis();
  firstCheckInState = true;
}

void updateStateTime()
{
  currentTimeInState = millis() - enteredStateTime;
}