#ifndef ULTRASONICSENSOR_HPP
#define ULTRASONICSENSOR_HPP
#include "distancesensor.hpp"

#include <Arduino.h>
class Ultrasonic;

class UltrasonicSensor : public DistanceSensor{
    private :
        Ultrasonic* _ultrasonic;   // the Arduino ultrasonic object is owned by this class
    public :
        using DistanceSensor::DistanceSensor;
        void begin() override;
    float MeasureInCentimeters() override;
    ~UltrasonicSensor() override;
};
#endif // UltraSonicSensor

 