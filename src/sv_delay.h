#ifndef _SV_DELAY_H_
#define _SV_DELAY_H_

//---------------------------------------------------------------------------
class Delay
{
  private:
    float rise;
    float fall;
  public:
    Delay(float rise = 0, float fall = 0);
    Delay(const Delay& delay);
    void setRise(float rise);
    float getRise();
    void setFall(float fall);
    float getFall();
};

#endif

