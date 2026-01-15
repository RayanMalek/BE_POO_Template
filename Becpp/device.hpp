#ifndef DEVICE_HPP
#define DEVICE_HPP

class Device{
  public:
  virtual void begin()=0;// virtual to allow polymorphism
  virtual ~Device()= default; // destructor
};

#endif