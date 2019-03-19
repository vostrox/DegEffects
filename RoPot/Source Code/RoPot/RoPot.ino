const int MillisecondsToWaitBetweenEachMidiRxCheck = 100;

const byte ControlChangeByte = 1011;
const byte ProgramChangeByte = 1100;

byte ChannelNumber = 15;

void setup()
{
  Serial1.begin(31250);
}

void loop()
{
  CheckMidi();
  delay(MillisecondsToWaitBetweenEachMidiRxCheck);
}
