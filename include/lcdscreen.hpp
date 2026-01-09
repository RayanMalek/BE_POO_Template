#ifndef LCDSCREEN_HPP
#define LCDSCREEN_HPP

#include<Arduino.h>
#include"device.hpp"

class lcdscreen : public device {
private :
  int cols;
  int rows;
  

public :
    lcdscreen(int cols,int rows);// Constructor: define geometry (not hardware yet)

    void begin() override;// mandatory for each device

    void clear();// clears the screen
    void printtext(int row,int col,const char* text);
    void printnumber(int row,int col,int value);

};
#endif