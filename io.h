#ifndef __IO__
#define __IO__

void setupGreenLeds();
void setupLs();
void setupButtons();
void setupDisplay();
void setupIO();

void greenLedsOff();
void pulseLs();

void displayMessage(char message[]);

#endif