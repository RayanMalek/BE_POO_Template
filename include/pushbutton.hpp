#ifndef PUSHBUTTON_HPP
#define PUSHBUTTON_HPP


#include <Arduino.h>
#include "digitalinput.hpp"

class pushbutton:public digitalinput{
  public :
  using digitalinput ::digitalinput;

  void begin() override;
  bool ishigh() override;
  ~pushbutton() override = default;

};
#endif