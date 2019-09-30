#include "src/Logger/Logger.h"
#include "Midi.h"
#include "Display.h"

const int MillisecondsToWaitBetweenEachMidiRxCheck = 100;
//Logger _logger;
Midi _midi;
Display _display;
bool on = true;

void setup()
{
  //_logger.Initialise(true);
  _midi.Initialise();
  _display.Initialise();
  //_logger.Info("Objects initialised");
}

void loop()
{
  //_midi.CheckMidi();
  //delay(MillisecondsToWaitBetweenEachMidiRxCheck);

  for (uint8_t i=0; i<127; i++)
  {
    _display.DisplayPreset(i, 0);
    delay(100);
  }
}
