#include "sv_delay.h"

//---------------------------------------------------------------------------
Delay::Delay(float rise, float fall)
{
  this->rise = rise;
  this->fall = fall;
}

//---------------------------------------------------------------------------
Delay::Delay(const Delay& delay)
{
  this->rise = delay.rise;
  this->fall = delay.fall;
}

//---------------------------------------------------------------------------
void Delay::setRise(float rise)
{
  this->rise = rise;
}

//---------------------------------------------------------------------------
float Delay::getRise()
{
  return rise;
}

//---------------------------------------------------------------------------
void Delay::setFall(float fall)
{
  this->fall = fall;
}

//---------------------------------------------------------------------------
float Delay::getFall()
{
  return fall;
}

