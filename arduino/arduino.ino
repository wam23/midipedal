/*
Board: Arduino Uno
Hardware: todo
Libraries: MIDIUSB, ezButton
*/

#include <ezButton.h>

#define CHANNEL = 1

ezButton btn1(7);
int pot1 = 0;

void setup()
{
  Serial.begin(115200);

  btn1.setDebounceTime(50);
}

void loop()
{
  btn1.loop();
  pot1 = readPotentiometer(A0, pot1);

  if (btn1.isPressed())
  {
    controlChange(1, 1);
  }
}

int readPotentiometer(uint8_t pin, int oldValue)
{
  int rawValue = analogRead(pin);

  if (abs(oldValue - rawValue) > 5)
  {
    int value = map(rawValue, 0, 1024, 0, 127);
    controlChange(pin, value);
    return rawValue;
  }
  else
  {
    return oldValue;
  }
}

void controlChange(byte control, byte value)
{
  Serial.print("send MIDI CC control ");
  Serial.print(control);
  Serial.print(" = ");
  Serial.println(value);

  control = constrain(control, 0, 119);
  value = constrain(value, 0, 127);

  // First parameter is the event type (0x0B = control change).
  // Second parameter is the event type, combined with the channel.
  // Third parameter is the control number number (0-119).
  // Fourth parameter is the control value (0-127).
  // midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  // MidiUSB.sendMIDI(event);
}