#ifndef PUSHUPDETECTOR_HPP
#define PUSHUPDETECTOR_HPP

#include <Arduino.h>

class PushUpDetector{
 private :
    int th;
    bool armed;
    unsigned long lastCountMs;
    unsigned long coolDownMs;
    unsigned long lastReadMs;
    unsigned long readPeriodMs;

  public :
  PushUpDetector(int th,unsigned long cooldownMs,unsigned long readPeriodMs);
  
  bool update(long d,unsigned long nowMs);
};
#endif