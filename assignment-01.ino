// #include <LiquidCrystal_I2C.h>
// #include <avr/sleep.h>
// #include <avr/power.h>
#include <core.h>
#include <kernel.h>

void setup()
{

}

void loop()
{
  // put your main code here, to run repeatedly:
  switch (getCurrentState())
  {
  case ST_INITIAL:
    break;
  case ST_SLEEP:
    break;
  default:
    break;
  }
}