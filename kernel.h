#ifndef __KERNEL__
#define __KERNEL__

#include "Arduino.h"

typedef enum
{
    ST_INITIAL,
    ST_SLEEP,
    ST_SETUP,
    ST_ROUND,
    ST_LSOE,
    ST_WIN,
} State;

void initKernel();
void updateStateTime();
void changeState(State newState);

State getCurrentState();

long getCurrentTimeInState();
long getEnteredStateTime();
bool isJustEnteredInState();

#endif