#ifndef _PUSH_BUTTON__H_
#define _PUSH_BUTTON__H_

class PushButton
{
private:
  OneShot    m_os;          // one-shot for lockout period
  const byte m_pin;         // pin to read
  const bool m_activeLevel; // true for active high input,
                            // false for active low input
  
public:
  PushButton(
    const byte pin,         // digital input pin
    const byte active,      // active LOW or HIGH
    const unsigned int dly  // lockout time in msec
  ) : m_os(OneShot(dly)), m_pin(pin), m_activeLevel(active != LOW)
  {
  }

  virtual bool update()
  {
    // Unlike most subclasses of StateMachine, this class does not
    // return true on update every time the underlying StateMachine
    // updates, but only when all of the following conditions are met:
    // (a) the embedded OneShot updates,
    // (b) the OneShot has not been triggered or has timed out since
    //     its last trigger, and
    // (c) the input pin is in its ACTIVE state.
    // When these conditions are met, the OneShot is triggered.
    // Since this method only returns true at the moment the trigger
    // occurs, a separate method to get the PushButton state is not
    // needed.
    if (m_os.update() 
      && !m_os.isTriggered() 
      && (digitalRead(m_pin) == (m_activeLevel ? HIGH : LOW))) {
      // Conditions are met, trigger the OneShot and return true.
      m_os.trigger();
      return true;
    }
    // Otherwise return false.
    return false;
  }
};

#endif

