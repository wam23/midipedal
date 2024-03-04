/*
Board: todo
Hardware: todo
Libraries: MIDIUSB, ezButton, MagicPot
*/

#define CHANNEL = 1

void setup()
{
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  // x = map(x, 0, 1024, 0, 127);
  // x = constrain(x, 0, 127)
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