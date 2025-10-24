#include "io.h"
#include "core.h"
#include "kernel.h"
#include "config.h"

void setup()
{
  initCore();
  setupIO();
  changeState(ST_INITIAL);
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