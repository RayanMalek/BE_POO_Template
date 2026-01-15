
#include "pushbutton.hpp"

void PushButton::begin(){
    pinMode(pin_, INPUT_PULLUP);

}

PushButton :: operator bool() const{
    return digitalRead(pin_)==LOW;

  }
bool PushButton::isPressed(){
  return digitalRead(pin_)==LOW;
} 

PushButton::Event PushButton::poll(unsigned long nowMs) {
  bool raw = isPressed(); // raw pressed?

  // debounce: if raw changes, reset timer
  if (raw != lastRaw_) {
    lastRaw_ = raw;
    lastChangeMs_ = nowMs;
  }

  // wait until stable long enough
  if (nowMs - lastChangeMs_ < DebounceMs) {
    return Event::None;
  }

  // update stable state
  if (raw != stable_) {
    stable_ = raw;

    if (stable_) {
      // became pressed
      pressed_ = true;
      pressStartMs_ = nowMs;
      return Event::None;
    } else {
      // became released -> generate event
      if (pressed_) {
        pressed_ = false;
        unsigned long held = nowMs - pressStartMs_;
        if (held >= LongPressMs) return Event::LongPress;
        return Event::ShortPress;
      }
    }
  }

  return Event::None;
}

