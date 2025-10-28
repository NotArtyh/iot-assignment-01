#ifndef __OUTPUT__
#define __OUTPUT__

typedef enum
{
    MSG_WELCOME

} Msg;

void greenLedsOff();
void pulseLs();

void displayMessage(Msg);

#endif