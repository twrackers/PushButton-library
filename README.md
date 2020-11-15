# PushButton #

The *PushButton* library supports connecting a momentary pushbutton, either normally-open (NO) or normally-closed (NC), to an Arduino GPIO pin.  It uses a `OneShot` object to provide debouncing logic to filter out either intermittent connections when opening or closing the pushbutton's contacts, and if desired to screen out button pushes which occur too close together.

## Examples ##

The repository includes a `PushButton_test` sketch in the `examples` directory.  The sketch defines a `PushButton` object connected to GPIO pin 7 with a 500 millisecond timeout period.  As written, the sketch expects a normally-open momentary pushbutton to be connected between pin 7 and ground.  Each time the button is pressed, "ping" will be written to the Arduino IDE's serial console.  If the button is pressed twice within a half-second, the second press will be filtered out.

The `PushButton_test` sketch requires the *OneShot* library ([https://github.com/twrackers/OneShot-library](https://github.com/twrackers/OneShot-library)) and the *StateMachine* library ([https://github.com/twrackers/StateMachine-library](https://github.com/twrackers/StateMachine-library)), in addition to the *PushButton* library.

## Dependencies ##

The *PushButton* library depends on the installation of the *OneShot* library ([https://github.com/twrackers/OneShot-library](https://github.com/twrackers/OneShot-library)) and the *StateMachine* library ([https://github.com/twrackers/StateMachine-library](https://github.com/twrackers/StateMachine-library)).

## Installation ##

Instructions for installing the *PushButton* library can be found in file `INSTALL.md` in this repository at [https://github.com/twrackers/PushButton-library/blob/main/INSTALL.md](https://github.com/twrackers/PushButton-library/blob/main/INSTALL.md).