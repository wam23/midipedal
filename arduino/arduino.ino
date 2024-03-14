/*
Board: SparkFun Pro Micro (atmega32U4)
Libraries: MIDIUSB, OneButton
*/

#include <OneButton.h>
#include <MIDIUSB.h>

OneButton btn1 = OneButton(7);
OneButton btn2 = OneButton(8);
OneButton btn3 = OneButton(9);
int pot1 = 0;
int pot2 = 0;

void setup()
{
  Serial.begin(115200);

  btn1.attachClick(handleClick, &btn1);
  btn1.attachDoubleClick(handleDoubleClick, &btn1);
  btn1.attachLongPressStart(handleLongPress, &btn1);

  btn2.attachClick(handleClick, &btn2);
  btn2.attachDoubleClick(handleDoubleClick, &btn2);
  btn2.attachLongPressStart(handleLongPress, &btn2);

  btn3.attachClick(handleClick, &btn3);
  btn3.attachDoubleClick(handleDoubleClick, &btn3);
  btn3.attachLongPressStart(handleLongPress, &btn3);
}

void loop()
{
  btn1.tick();
  btn2.tick();
  btn3.tick();
  pot1 = readPotentiometer(A0, pot1);
  // pot2 = readPotentiometer(A1, pot2);
}

void handleClick(OneButton *oneButton)
{
  patchChange(oneButton->pin(), 0);
}

void handleDoubleClick(OneButton *oneButton)
{
  patchChange(oneButton->pin(), 1);
}

void handleLongPress(OneButton *oneButton)
{
  patchChange(oneButton->pin(), 2);
}

int readPotentiometer(uint8_t pin, int oldValue)
{
  int rawValue = analogRead(pin);

  if (abs(oldValue - rawValue) > 5)
  {
    int value = map(rawValue, 0, 1024, 0, 127);
    controlChange(pin, 11, value);
    return rawValue;
  }
  else
  {
    return oldValue;
  }
}

void controlChange(byte channel, byte control, byte value)
{
  Serial.print("send MIDI control ");
  Serial.print(control);
  Serial.print(" = ");
  Serial.println(value);

  control = constrain(control, 0, 119);
  value = constrain(value, 0, 127);

  // First parameter is the event type (0x0B = control change).
  // Second parameter is the event type, combined with the channel.
  // Third parameter is the control number number (0-119).
  // Fourth parameter is the control value (0-127).
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
  MidiUSB.flush();
}

void patchChange(byte channel, byte value)
{
  Serial.print("send MIDI patch ");
  Serial.println(value);

  midiEventPacket_t event = {0x0C, 0xC0 | channel, value};
  MidiUSB.sendMIDI(event);
  MidiUSB.flush();
}
