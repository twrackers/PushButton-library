#include <Streaming.h>
#include <PushButton.h>

const byte pin = 7;
const int to = 500;

PushButton pb(pin, LOW, to);

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  if (pb.update()) {
    Serial << "ping" << endl;
  }
}
