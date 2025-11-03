#ifndef FSM_H
#define FSM_H

typedef enum {
    ST_INITIAL,
    ST_SLEEP,
    ST_SETUP,
    ST_ROUND,
    ST_LOSE,
    ST_WIN,
} state_t;

void fsm_init();
void fsm_update();

#endif