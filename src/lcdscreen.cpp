#include"rgb_lcd.h"
#include "Wire.h"
#include "lcdscreen.hpp"


static rgb_lcd lcd;// object lcd of type rgb_lcd with the necessary attributes 


lcdscreen::lcdscreen(int col,int row): cols(col),rows(row)
{}


void lcdscreen::begin(){
  Wire.begin();
  lcd.begin(cols,rows);
  lcd.setRGB(255,255,255);
  lcd.clear();
}

void lcdscreen ::clear(){
  lcd.clear();
}

void lcdscreen ::printtext(int row, int col, const char *text){
  lcd.setCursor(col,row);
  lcd.print(text);
}

void lcdscreen::printnumber(int row, int col, int value){
  lcd.setCursor(col,row);
  lcd.print(value);
}