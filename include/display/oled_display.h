#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

void oled_init();
void oled_test_print();
void oled_print(const char *text);
void oled_print_static(const char *text);

#endif