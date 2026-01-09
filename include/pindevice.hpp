#ifndef PINDEVICE_HPP
#define PINDEVICE_HPP
#include"device.hpp"

class pindevice :public device {
protected :
  int pin_;// protected so children can access it 
public :
  pindevice(int pin);// constructor every pin device must have a pin 
  ~pindevice() override;// destructor override cause virtual method in parent class 

};

#endif