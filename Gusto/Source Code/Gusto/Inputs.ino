#define KNOB_ERROR_VOLTS 0.1

double _previousKnobVoltage = 0;

void CheckTimeKnob()
{
  int value = analogRead(PIN_TIME_KNOB);
  double voltage = 5 - (value * (5.0 / 1023.0));
  
  double timeMs = (voltage / 5.0) * (TIME_MAXIMUM_DELAY_MILLISECONDS - TIME_MINIMUM_DELAY_MILLISECONDS) + TIME_MINIMUM_DELAY_MILLISECONDS;
  
  //Check that the knob has moved
  if (abs(voltage - _previousKnobVoltage) >= KNOB_ERROR_VOLTS)
  {
    TempoMs = timeMs;
    _previousKnobVoltage = voltage;
  }
}

void CheckSubDivisionSwitch()
{
  //Open-Quarter, 5k-DottedEighths, 0R-Eighths
  //Voltage divider, top resistor is switched, bottom is 10k
  
  int value = analogRead(PIN_SUBDIVISION);
  float voltage = value * (5.0 / 1023.0);

  //0V, no connection to 5v as switch is in off position (center)
  if (voltage < 1.0)
  {
    SubDivision = SUBDIVISION_QUARTER;
  }
  //3.3V, using 5k and 10k
  else if (voltage > 1.0 && voltage < 4.5)
  {
    SubDivision = SUBDIVISION_DOTTEDEIGHTHS;
  }
  //5V, using 0R and 10k
  else
  {
    SubDivision = SUBDIVISION_EIGHTHS;
  }
}

void CheckModulationSwitch()
{
  //Open-Off, 5k-Light, 0R-Deep
  //Voltage divider, top resistor is switched, bottom is 10k
  
  int value = analogRead(PIN_MODULATION_TYPE);
  float voltage = value * (5.0 / 1023.0);

  //0V, no connection to 5v as switch is in off position (center)
  if (voltage < 1.0)
  {
    ModulationType = MODULATION_TYPE_OFF;
  }
  //3.3V, using 5k and 10k
  else if (voltage > 1.0 && voltage < 4.5)
  {
    ModulationType = MODULATION_TYPE_LIGHT;
  }
  //5V, using 0R and 10k
  else
  {
    ModulationType = MODULATION_TYPE_DEEP;
  }
}
