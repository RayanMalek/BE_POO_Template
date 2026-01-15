#include <Ultrasonic.h>
#include "ultrasonicsensor.hpp"

void UltrasonicSensor::begin(){
  _ultrasonic= new Ultrasonic(pin_);
}

float UltrasonicSensor::MeasureInCentimeters() {
  return _ultrasonic->MeasureInCentimeters();
}
UltrasonicSensor::~UltrasonicSensor() {
  delete _ultrasonic;
  _ultrasonic = nullptr;
}