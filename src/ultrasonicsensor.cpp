#include <Ultrasonic.h>
#include "ultrasonicsensor.hpp"



void ultrasonicsensor::begin(){
  _ultrasonic=  new Ultrasonic(pin_);
}

float ultrasonicsensor::MeasureInCentimeters() {
  return _ultrasonic->MeasureInCentimeters();
}
ultrasonicsensor::~ultrasonicsensor() {
  delete _ultrasonic;
  _ultrasonic = nullptr;
}