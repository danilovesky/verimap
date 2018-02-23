#include "sv_range.h"

//---------------------------------------------------------------------------
Range::Range(int from, int to)
{
  this->from = from;
  this->to = to;
}

//---------------------------------------------------------------------------
Range::Range(const Range& range)
{
  this->from = range.from;
  this->to = range.to;
}

//---------------------------------------------------------------------------
void Range::setFrom(int from)
{
  this->from = from;
}

//---------------------------------------------------------------------------
int Range::getFrom()
{
  return this->from;
}

//---------------------------------------------------------------------------
void Range::setTo(int to)
{
  this->to = to;
}

//---------------------------------------------------------------------------
int Range::getTo()
{
  return to;
}

//---------------------------------------------------------------------------
int Range::getLow()
{
  if (this->from < this->to)
    return this->from;
  else
    return this->to;
}

//---------------------------------------------------------------------------
int Range::getHigh()
{
  if (this->from > this->to)
    return this->from;
  else
    return this->to;
}

//---------------------------------------------------------------------------
int Range::getInc()
{
  if (this->from <= this->to)
    return 1;
  else
    return -1;
}

//---------------------------------------------------------------------------
int Range::getWidth()
{
  if (this->from <= this->to)
    return (this->to - this->from + 1);
  else
    return (this->from - this->to + 1);
}

//---------------------------------------------------------------------------
bool Range::isIn(int index)
{
  return (((index >= this->from) && (index <= this->to)) || ((index >= this->to) && (index <= this->from)));
}

