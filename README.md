# PushButton #

The *PushButton* library supports connecting a momentary pushbutton, either normally-open (NO) or normally-closed (NC), to an Arduino GPIO pin.  It uses a `OneShot` object to provide debouncing logic to filter out either intermittent connections when opening or closing the pushbutton's contacts, and if desired to screen out button pushes which occur too close together.

## Examples ##

The repository includes a `PushButton_test` sketch in the `examples` directory.  The sketch defines a `PushButton` object connected to GPIO pin 7 with a 500 millisecond timeout period.  As written, the sketch expects a normally-open momentary pushbutton to be connected between pin 7 and ground.  Each time the button is pressed, "ping" will be written to the Arduino IDE's serial console.  If the button is pressed twice within a half-second, the second press will be filtered out.

The `PushButton_test` sketch requires the *OneShot* library ([https://github.com/twrackers/OneShot-library](https://github.com/twrackers/OneShot-library)) and the *StateMachine* library ([https://github.com/twrackers/StateMachine-library](https://github.com/twrackers/StateMachine-library)), in addition to the *PushButton* library.

## Dependencies ##

The *PushButton* library depends on the installation of the *OneShot* library ([https://github.com/twrackers/OneShot-library](https://github.com/twrackers/OneShot-library)) and the *StateMachine* library ([https://github.com/twrackers/StateMachine-library](https://github.com/twrackers/StateMachine-library)).

## Installation ##

Instructions for installing the *PushButton* library can be found in file `INSTALL.md` in this repository at [https://github.com/twrackers/PushButton-library/blob/main/INSTALL.md](https://github.com/twrackers/PushButton-library/blob/main/INSTALL.md).

## API ##

### *PushButton(const byte pin, const byte active, const unsigned int dly)* ###

The constructor creates an instance of a `PushButton` object.

#### Arguments ####

- **pin: const byte:** GPIO pin to which pushbutton is connected.
- **active: const byte:** `HIGH` or `LOW` to indicate what a `digitalRead()` call would return when the pushbutton is pressed.
- **dly: const unsigned int:** Debounce time in milliseconds.  Once a press of the pushbutton is detected, no further detections will occur until `dly` milliseconds have passed.

### *virtual bool update()* ###

Derived from `StateMachine::update()`, this method should be called from within the Arduino sketch's `loop()` function.  Unlike the behavior of `update()` in most subclasses of `StateMachine`, the `update()` method of a `PushButton` object only returns `true` when the following conditions are all met.

1. The `OneShot` object embedded in the `PushButton` updates its state.
2. The `OneShot` has either not been triggered yet, or it has timed out since its most recent trigger.
3. The attached GPIO pin has returned to its non-ACTIVE state at some point since the `OneShot` was last triggered.
4. The attached GPIO pin is now in its ACTIVE state.

In short, `update()` only returns `true` when the GPIO pin goes from inactive to active from one sample of the pin to the next.  No further inactive-to-active transitions will be detected until after the delay period has elapsed.

#### Returns ####

- **bool:** `true` if new press of pushbutton is sensed after any previous press has timed out.

### *void clear()* ###

Terminates the delay interval early after a button press.
