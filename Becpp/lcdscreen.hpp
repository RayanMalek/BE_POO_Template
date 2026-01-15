#ifndef LCDSCREEN_HPP
#define LCDSCREEN_HPP

#include <Arduino.h>
#include "device.hpp"


class LcdScreen : public Device {
private:
  int cols;
  int rows;

public:
  LcdScreen(int cols, int rows);
  void begin() override;

  // low-level
  void clear();
  void printtext(int row, int col, const char* text);
  void printnumber(int row, int col, int value);

  // high-level screens (NEW)
  void showIdle();
  void showCounting(int reps);
  void showSummary(int reps, int rank);
  void showLeaderboardEntry(int index1based, int reps); // e.g. #1 with 42 reps
  void showLeaderboardEmpty();                          // when no scores yet
};

#endif
