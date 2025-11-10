#ifndef BUTTON_H
#define BUTTON_H

void button_init();
void button_reset();
bool button_is_pressed(int index);
int button_get_current_pressed();

#endif