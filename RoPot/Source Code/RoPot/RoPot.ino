#include "src/Logger/Logger.h"
#include "Midi.h"

const int MillisecondsToWaitBetweenEachMidiRxCheck = 100;
Logger logger;
Midi midi;

void setup()
{
  logger.Initialise(true);
  midi.Initialise();
  
  logger.Error("Test");
}

void loop()
{
  midi.CheckMidi();
  delay(MillisecondsToWaitBetweenEachMidiRxCheck);
}
