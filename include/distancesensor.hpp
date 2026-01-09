#ifndef DISTANCESENSOR_HPP
#define DISTANCESENSOR_HPP

#include"pindevice.hpp"

class distancesensor: public pindevice{
  public :
  using pindevice::pindevice;//so the child of distancesensor can use pindevice(int pin ) without rewriting the ocnstructor
  virtual float MeasureInCentimeters()=0; // child implements the method 
  ~distancesensor() override = default;




};

#endif 