#ifndef LED_H
#define LED_H

void led_init();
void status_led_pulse();
void status_led_off();
void status_led_on();
void green_led_off();
void green_led_on();
void green_led_blink_sequence();
void green_led_on_index(int i);

#endif