#ifndef __KERNEL__
#define __KERNEL__

typedef enum {
    ST_INITIAL,
    ST_SLEEP,
    ST_SETUP,
    ST_ROUND,
    ST_LSOE,
    ST_WIN,
} State;

State getCurrentState();

#endif