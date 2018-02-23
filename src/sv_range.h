#ifndef _SV_RANGE_H_
#define _SV_RANGE_H_

//---------------------------------------------------------------------------
class Range
{
  private:
    int from;
    int to;
  public:
    Range(int from = 0, int to = 0);
    Range(const Range& range);
    void setFrom(int from);
    int getFrom();
    void setTo(int to);
    int getTo();
    int getLow();
    int getHigh();
    int getInc();
    int getWidth();
    bool isIn(int index);
};

#endif

