#ifndef DIGITALINPUT_HPP
#define DIGITALINPUT_HPP
#include"pindevice.hpp"

class digitalinput: public pindevice{
  public :
  using pindevice::pindevice; // so the child of digital input can use pindevice(int pin ) without rewriting the ocnstructor
  virtual bool ishigh()=0; // child implements the method 
  ~digitalinput() override = default;



};

#endif 