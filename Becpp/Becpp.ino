#include "ultrasonicsensor.hpp"
#include "pushupdetector.hpp"
#include "pushbutton.hpp"
#include "lcdscreen.hpp"

#define UltrasonicPin  D6
#define PushButtonPin  D5

const int th = 10;
const unsigned long cooldownMs   = 400; // ignore repeats for 0.4s after a rep
const unsigned long readPeriodMs = 50;  // sensor read rate

static unsigned long lastSampleMs = 0;

ultrasonicsensor sensor(UltrasonicPin);
pushbutton       activate(PushButtonPin);
pushupdetector   detector(th, cooldownMs, readPeriodMs);
lcdscreen        screen(20, 2);

enum class AppState { Idle, Counting, Summary, Leaderboard };
AppState state = AppState::Idle;

int counter  = 0;
int lastRank = 0;
int lbIndex  = 0;

static const int TOPK = 5;
int topScores[TOPK] = {0, 0, 0, 0, 0};
int topCount = 0;

// edge detect for button press
bool lastBtn = false;

// ---------- Leaderboard insert (Top 5, descending) ----------
int leaderboardInsert(int reps) {
  if (reps <= 0) return 0;

  int pos = 0;
  while (pos < topCount && topScores[pos] >= reps) pos++;

  if (topCount < TOPK) {
    for (int i = topCount; i > pos; --i) topScores[i] = topScores[i - 1];
    topScores[pos] = reps;
    topCount++;
    return pos + 1;
  }

  if (pos >= TOPK) return 0;

  for (int i = TOPK - 1; i > pos; --i) topScores[i] = topScores[i - 1];
  topScores[pos] = reps;
  return pos + 1;
}

// ---------- Show one leaderboard page ----------
void showLeaderboard(int idx) {
  if (topCount == 0) {
    screen.showLeaderboardEmpty();
  } else {
    // idx is 0..topCount-1
    screen.showLeaderboardEntry(idx + 1, topScores[idx]);
  }
}

// ---------- Arduino setup ----------
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.begin(9600);
  delay(300);

  screen.begin();
  screen.showIdle();

  // If your ultrasonicsensor class doesn't have begin(), comment this out.
  sensor.begin();

  activate.begin();
  delay(50);                       // let the input settle
  lastBtn = activate;  // sync edge detector to current state


  Serial.println("Press the button to get started");
}

// ---------- Arduino loop ----------
void loop() {
  unsigned long now = millis();

  // Create a single "press event" from ispressed()
  bool pressed = activate ;      // true while held
  bool pressEvent = (pressed && !lastBtn);     // rising edge
  lastBtn = pressed;

  switch (state) {
    case AppState::Idle: {
      if (pressEvent) {
        counter  = 0;
        lastRank = 0;

        state = AppState::Counting;
        screen.showCounting(counter);

        Serial.println("Started session");
        delay(150); // small guard
      }
      return;
    }

    case AppState::Counting: {
      // short press ends session
      if (pressEvent) {
        lastRank = leaderboardInsert(counter);

        state = AppState::Summary;
        screen.showSummary(counter, lastRank);

        Serial.print("Session ended. Reps=");
        Serial.print(counter);
        Serial.print(" Rank=");
        Serial.println(lastRank);

        delay(150);
        return;
      }

      // pace sensor reads
      if (now - lastSampleMs < readPeriodMs) return;
      lastSampleMs = now;

      long d = sensor.MeasureInCentimeters();

      if (detector.update(d, now)) {
        counter++;
        // simple (may clear screen each rep depending on your lcdscreen::showCounting)
        screen.showCounting(counter);

        Serial.print("push up : ");
        Serial.println(counter);
      }

      return;
    }

    case AppState::Summary: {
      // press enters leaderboard browsing
      if (pressEvent) {
        state = AppState::Leaderboard;
        lbIndex = 0;
        showLeaderboard(lbIndex);
        delay(150);
      }
      return;
    }

    case AppState::Leaderboard: {
      // press cycles entries, then returns to idle
      if (pressEvent) {
        if (topCount == 0) {
          state = AppState::Idle;
          screen.showIdle();
        } else {
          lbIndex++;
          if (lbIndex >= topCount) {
            state = AppState::Idle;
            screen.showIdle();
          } else {
            showLeaderboard(lbIndex);
          }
        }
        delay(150);
      }
      return;
    }
  }
}
