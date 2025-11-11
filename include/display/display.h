#ifndef DISPLAY_H
#define DISPLAY_H

enum message {
    MSG_INITIAL,
    MSG_SLEEP,
    MSG_SETUP,
    MSG_LOSE,
    MSG_WIN,
};

void display_init();
void display_print(const char *text);
void display_test_print();
void display_print_P(message msg, ...);

#endif