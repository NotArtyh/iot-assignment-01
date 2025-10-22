#include <LiquidCrystal_I2C.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <config.h>

typedef enum
{
  ST_INITIAL,
  ST_SLEEP,
  ST_SETUP,
  ST_ROUND,
  ST_LSOE,
  ST_WIN,
} State;

// FADING LED VARIABLES
int fadeAmount;
int currIntensity;

// start first state (trovare un modo per non dichiararlo globalmente)
State currentState = ST_INITIAL;

void setup()
{

  // LS SETUP
  currIntensity = 0;
  fadeAmount = 5;
  pinMode(LS, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  switch (currentState)
  {
  case ST_INITIAL:
    handle_initial_state();
    fading_ls();

    // transiton
    break;
  case ST_SLEEP:

    break;
  default:
    break;
  }
}

void handle_initial_state()
{
  // In the initial state, all green leds should be off but led LS that pulses (fading in and out),
  // waiting for some player to start the game. The LCD should display the message “Welcome to TOS! Press B1 to Start” (on multiple lines).

  display_message_lcd("Welcome to TOS! Press B1 to Start");
}

void display_message_lcd(char message[])
{
}

void fading_ls()
{
  analogWrite(LS, currIntensity);
  currIntensity = currIntensity + fadeAmount;
  if (currIntensity == 0 || currIntensity == 255)
  {
    fadeAmount = -fadeAmount;
  }
  delay(20);
}