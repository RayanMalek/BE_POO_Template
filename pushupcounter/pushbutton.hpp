#ifndef PUSHBUTTON_HPP
#define PUSHBUTTON_HPP

#include <Arduino.h>
#include "digitalinput.hpp"


class PushButton : public DigitalInput{
  public :
  using DigitalInput::DigitalInput;

  enum class Event {None, ShortPress,LongPress};

  Event poll(unsigned long nowMs);
  void begin() override;
  bool isPressed() override;
  ~PushButton() override = default;

  operator bool() const;

  private :
  bool lastRaw_ = false;                  // last raw pressed reading
  bool stable_  = false;                  // debounced pressed state
  unsigned long lastChangeMs_ = 0;

  bool pressed_ = false;
  unsigned long pressStartMs_ = 0;

  static const unsigned long DebounceMs = 30;
  static const unsigned long LongPressMs = 800;

};
#endif