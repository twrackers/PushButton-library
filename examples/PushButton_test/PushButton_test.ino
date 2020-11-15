#include <PushButton.h>

const byte pin = 7;
const int timeout = 500;

// Use momentary normally-open pushbutton connected between
// pin 7 and ground.
PushButton pb(pin, LOW, timeout);

void setup() 
{
  Serial.begin(115200);
  pinMode(pin, INPUT_PULLUP);
}

void loop() 
{
  if (pb.update()) {
    Serial.println("ping");
  }
}
