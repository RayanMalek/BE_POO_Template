#ifndef PUSHUPDETECTOR_HPP
#define PUSHUPDETECTOR_HPP

#include <Arduino.h>

class pushupdetector{
 private :
    int th;
    bool armed;
    unsigned long lastCountMs;
    unsigned long cooldownMs;
    unsigned long lastReadMs;
    unsigned long readPeriodMs;

  public :
  pushupdetector(int th,unsigned long cooldownMs,unsigned long readPeriodMs);
  
  bool update(long d,unsigned long nowMs);
};
#endif