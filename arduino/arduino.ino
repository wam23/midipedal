/*
Board: Arduino Uno
Hardware: todo
Libraries: MIDIUSB, ezButton, MagicPot
*/

#include <ezButton.h>
#include <MagicPot.h>

#define CHANNEL = 1

int waitTime = 100;
ezButton btn1(7);
MagicPot potentiometer(A0);

void setup()
{
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);

  btn1.setDebounceTime(50);
  potentiometer.begin();
  potentiometer.onChange(onPotentiometerChange);
}

void loop()
{
  btn1.loop();
  potentiometer.read(2);

  if (btn1.isPressed())
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(waitTime);
    digitalWrite(LED_BUILTIN, LOW);
    delay(waitTime);
  }

  // x = map(x, 0, 1024, 0, 127);
  // x = constrain(x, 0, 127)
}

void onPotentiometerChange() {
  Serial.println(potentiometer.getValue());
}

void controlChange(byte control, byte value)
{
  Serial.print("send MIDI CC control ");
  Serial.print(control);
  Serial.print(" = ");
  Serial.println(value);

  // First parameter is the event type (0x0B = control change).
  // Second parameter is the event type, combined with the channel.
  // Third parameter is the control number number (0-119).
  // Fourth parameter is the control value (0-127).
  // midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  // MidiUSB.sendMIDI(event);
}