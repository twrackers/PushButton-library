#ifndef _PUSH_BUTTON__H_
#define _PUSH_BUTTON__H_

#include <OneShot.h>

// Implements class to read a digital input pin, with a lockout
// period to provide debounce.  Useful for reading a momentary pushbutton.
//
// Dependencies
//   PushButton
//   `--uses--> OneShot
//              `--isa--> StateMachine
class PushButton
{
private:
  OneShot    m_os;          // one-shot for lockout period
  const byte m_pin;         // pin to read
  const bool m_activeLevel; // true for active high input (pull up on close),
                            // false for active low input (pull down on close)
  bool       m_released;    // true if button has gone inactive
  bool       m_pullup;      // true if INPUT_PULLUP selected, false for INPUT
  enum E_STATE {
    eInactive, eTiming, eStillPressed
  } m_state;
  
public:
  PushButton(
    const byte pin,         // digital input pin
    const byte active,      // active LOW or HIGH
    const unsigned int dly  // lockout time in msec
  ) : m_os(OneShot(dly)), m_pin(pin), m_activeLevel(active != LOW),
  m_released(true), m_pullup(true), m_state(eInactive)
  {
    pinMode(m_pin, INPUT_PULLUP);   // use pull-up in case pushbutton has
                                    // open-circuit state
  }

  virtual bool update()
  {
    // Unlike most subclasses of StateMachine, this class does not
    // return true on update every time the underlying StateMachine
    // updates, but only when all of the following conditions are met:
    // (a) the embedded OneShot updates,
    // (b) the OneShot has not been triggered or has timed out since
    //     its last trigger,
    // (c) the input pin has returned to its INACTIVE state at some point
    //     since the OneShot was triggered, and
    // (d) the input pin is now in its ACTIVE state.
    // When these conditions are met, the OneShot is triggered.
    // Since this method only returns true at the moment the trigger
    // occurs, a separate method to get the PushButton state is not
    // needed.
    if (m_os.update()) {
      bool active = (digitalRead(m_pin) == (m_activeLevel ? HIGH : LOW));
      if (m_state == eInactive) {
        // Button wasn't pressed, timeout period passed.
        if (active) {
          m_os.trigger();
          m_state = eTiming;
          return true;
        }
      } else if (m_state == eTiming) {
        // In timeout period. 
        if (!m_os.isTriggered()) {
          if (!active) {
            m_state = eInactive;
          } else {
            m_state = eStillPressed;
          }
        }
      } else /* if (m_state == eStillPressed) */ {
        if (!active) {
          m_state = eInactive;
        }
      }
    }
    return false;
  }
  
  void clear()
  {
    m_os.clear();
  }

  void setPullup(const bool enable) {
    m_pullup = enable;
    pinMode(m_pin, m_pullup ? INPUT_PULLUP : INPUT);
  }

  bool isPullup() const {
    return m_pullup;
  }
};

#endif

