#ifndef DIGITALINPUT_HPP
#define DIGITALINPUT_HPP
#include "pindevice.hpp"

class DigitalInput : public PinDevice{
  public :

  using PinDevice::PinDevice; // so the child of digital input can use pindevice(int pin ) without rewriting the ocnstructor
  virtual bool isPressed()=0; // child implements the method 
  ~DigitalInput() override = default;
};

#endif 