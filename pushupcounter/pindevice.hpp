#ifndef PINDEVICE_HPP
#define PINDEVICE_HPP
#include "device.hpp"

class PinDevice : public Device {
protected :
  int pin_;// protected so children can access it 
public :
  PinDevice(int pin);// constructor every pin device must have a pin 
  ~PinDevice() override;// destructor override cause virtual method in parent class 
};

#endif