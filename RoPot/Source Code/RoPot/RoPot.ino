#include "src/Logger/Logger.h"

const int MillisecondsToWaitBetweenEachMidiRxCheck = 100;
const int MidiBaudRate = 31250;
byte ChannelNumber = 15;
Logger logger;

void setup()
{
  logger.Initialise(true);
  Serial1.begin(MidiBaudRate);
  while(!Serial1);
  logger.Error("Test");
}

void loop()
{
  CheckMidi();
  delay(MillisecondsToWaitBetweenEachMidiRxCheck);
}
