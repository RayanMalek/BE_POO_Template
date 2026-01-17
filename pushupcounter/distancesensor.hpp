#ifndef DISTANCESENSOR_HPP
#define DISTANCESENSOR_HPP

#include "pindevice.hpp"

class DistanceSensor: public PinDevice{
  public :
  using PinDevice::PinDevice;//so the child of distancesensor can use pindevice(int pin ) without rewriting the ocnstructor
  virtual float MeasureInCentimeters()=0; // child implements the method 
  ~DistanceSensor() override = default;

};

#endif 