#include "rgb_lcd.h"
#include "Wire.h"
#include "lcdscreen.hpp"

static rgb_lcd lcd;

LcdScreen::LcdScreen(int col, int row) : cols(col), rows(row) {}

void LcdScreen::begin() {
  Wire.begin();
  lcd.begin(cols, rows);
  lcd.setRGB(255, 255, 255);
  lcd.clear();
}

void LcdScreen::clear() {
  lcd.clear();
}

void LcdScreen::printtext(int row, int col, const char *text) {
  lcd.setCursor(col, row);
  lcd.print(text);
}

void LcdScreen::printnumber(int row, int col, int value) {
  lcd.setCursor(col, row);


  lcd.print(value);
}

// -------------------- High-level UI screens --------------------

void LcdScreen::showIdle() {
  clear();
  printtext(0, 0, "Push-up counter");
  printtext(1, 0, "Press button");
}

void LcdScreen::showCounting(int reps) {
  clear();
  printtext(0, 0, "Counting...");
  printtext(1, 0, "Reps: ");
  printnumber(1, 6, reps);
}

void LcdScreen::showSummary(int reps, int rank) {
  clear();
  printtext(0, 0, "Session:");
  printnumber(0, 9, reps);
  printtext(0, 13, "reps");

  printtext(1, 0, "Rank:");
  if (rank <= 0) {
    printtext(1, 6, "-- press");
  } else {
    printtext(1, 6, "#");
    printnumber(1, 7, rank);
    printtext(1, 10, " press");
  }
}

void LcdScreen::showLeaderboardEntry(int index1based, int reps) {
  clear();
  printtext(0, 0, "Top5 #");
  printnumber(0, 6, index1based);
  printtext(1, 0, "Reps:");
  printnumber(1, 6, reps);
}

void LcdScreen::showLeaderboardEmpty() {
  clear();
  printtext(0, 0, "Top 5 empty");
  printtext(1, 0, "Press to exit");
}
