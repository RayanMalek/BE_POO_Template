#include "rgb_lcd.h"
#include "Wire.h"
#include "lcdscreen.hpp"

static rgb_lcd lcd;

lcdscreen::lcdscreen(int col, int row) : cols(col), rows(row) {}

void lcdscreen::begin() {
  Wire.begin();
  lcd.begin(cols, rows);
  lcd.setRGB(255, 255, 255);
  lcd.clear();
}

void lcdscreen::clear() {
  lcd.clear();
}

void lcdscreen::printtext(int row, int col, const char *text) {
  lcd.setCursor(col, row);
  lcd.print(text);
}

void lcdscreen::printnumber(int row, int col, int value) {
  lcd.setCursor(col, row);
  lcd.print(value);
}

// -------------------- High-level UI screens --------------------

void lcdscreen::showIdle() {
  clear();
  printtext(0, 0, "Push-up counter");
  printtext(1, 0, "Press button");
}

void lcdscreen::showCounting(int reps) {
  // If you want a full refresh:
  // clear();
  // printtext(0, 0, "Counting...");
  // printtext(1, 0, "Reps: 0");

  // Better: draw the static once and update reps separately in main,
  // but simplest is this:
  clear();
  printtext(0, 0, "Counting...");
  printtext(1, 0, "Reps: ");
  printnumber(1, 6, reps);
}

void lcdscreen::showSummary(int reps, int rank) {
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

void lcdscreen::showLeaderboardEntry(int index1based, int reps) {
  clear();
  printtext(0, 0, "Top5 #");
  printnumber(0, 6, index1based);

  printtext(1, 0, "Reps:");
  printnumber(1, 6, reps);
}

void lcdscreen::showLeaderboardEmpty() {
  clear();
  printtext(0, 0, "Top 5 empty");
  printtext(1, 0, "Press to exit");
}
