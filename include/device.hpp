#ifndef DEVICE_HPP
#define DEVICE_HPP


class device{
  public:
  virtual void begin()=0;// virtual to allow polymorphism
  virtual ~device()= default; // destructor
};

#endif