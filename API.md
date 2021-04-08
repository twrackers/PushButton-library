# PushButton library API #

### *PushButton(const byte pin, const byte active, const unsigned int dly)* ###

The constructor creates an instance of a `PushButton` object.

#### Arguments ####

- *pin: const byte*: GPIO pin to which pushbutton is connected.
- *active: const byte*: `HIGH` or `LOW` to indicate what a `digitalRead()` call would return when the pushbutton is pressed.
- *dly: const unsigned int*: Debounce time in milliseconds.  Once a press of the pushbutton is detected, no further detections will occur until `dly` milliseconds have passed.

### *virtual bool update()* ###

Derived from `StateMachine::update()`, this method should be called from within the Arduino sketch's `loop()` function.  Unlike the behavior of `update()` in most subclasses of `StateMachine`, the `update()` method of a `PushButton` object only returns `true` when the following conditions are all met.

1. The `OneShot` object embedded in the `PushButton` updates its state.
2. The `OneShot` has either not been triggered yet, or it has timed out since its most recent trigger.
3. The attached GPIO pin has returned to its non-ACTIVE state at some point since the `OneShot` was last triggered.
4. The attached GPIO pin is now in its ACTIVE state.

In short, `update()` only returns `true` when the GPIO pin goes from inactive to active from one sample of the pin to the next.  No further inactive-to-active transitions will be detected until after the delay period has elapsed.

#### Returns ####

- *bool*: `true` if new press of pushbutton is sensed after any previous press has timed out.

### *void clear()* ###

Terminates the delay interval early after a button press.

