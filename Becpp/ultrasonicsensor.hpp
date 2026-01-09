#ifndef ULTRASONICSENSOR_HPP
#define ULTRASONICSENSOR_HPP
#include"distancesensor.hpp"

#include <Arduino.h>
class Ultrasonic;
class ultrasonicsensor: public distancesensor{
private :
    
    Ultrasonic* _ultrasonic;   // the Arduino ultrasonic object is owned by this class


public :
    using distancesensor :: distancesensor;
    void begin() override;
    float MeasureInCentimeters() override;
    ~ultrasonicsensor() override;
};
#endif // UltraSonicSensor

