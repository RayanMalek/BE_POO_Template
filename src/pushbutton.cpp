
#include "pushbutton.hpp"



void pushbutton::begin(){
    pinMode(pin_, INPUT);

}

bool pushbutton ::ishigh(){
  return digitalRead(pin_)==HIGH;
} 