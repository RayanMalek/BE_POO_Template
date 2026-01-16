#include <Arduino.h>
#include "pushupdetector.hpp"

PushUpDetector::PushUpDetector(int _th,unsigned long _coolDownMs,unsigned long _readPeriodMs):
th(_th),
coolDownMs(_coolDownMs),
readPeriodMs(_readPeriodMs),
armed(true),
lastReadMs(0),
lastCountMs(0)

{

}

bool PushUpDetector::update(long d,unsigned long nowMs){
    if (nowMs - lastReadMs < readPeriodMs) return false;//Ignore sensor values if I checked too recently    
    lastReadMs = nowMs;

    
    if (d >= th) { // if user back up (d is big again ) rearm 
        armed = true;
    }

    // same as: if (armed && d>0 && d<th) { if(nowMs-lastCountMs > cooldownMs) { counter++; ... } }
    if (armed && d > 0 && d < th) { // if you were ready ( armed = true) and the use is down again 
        if (nowMs - lastCountMs > coolDownMs) { // and enough time passed since last push up 
            armed = false;
            lastCountMs = nowMs;
            return true; // rep detected
        }
    }
    return false;
}