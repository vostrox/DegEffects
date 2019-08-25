void CheckTimeKnob()
{
  int value = analogRead(PIN_TIME_KNOB);
  double voltage = value * (5.0 / 1023.0);
  
  double timeMs = (voltage / 5.0) * (TIME_MAXIMUM_DELAY_MILLISECONDS - TIME_MINIMUM_DELAY_MILLISECONDS) + TIME_MINIMUM_DELAY_MILLISECONDS;

  double difference = timeMs - TempoMs;
  if (abs(difference) >= TIME_KNOB_ERROR_MILLISECONDS)
  {
    TempoMs = timeMs;
  }
}

void CheckSubDivisionSwitch()
{
  //Open-Quarter, 5k-Eighths, 0R-DottedEighths
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
    SubDivision = SUBDIVISION_EIGHTHS;
  }
  //5V, using 0R and 10k
  else
  {
    SubDivision = SUBDIVISION_DOTTEDEIGHTHS;
  }
}

void CheckModulationSwitch()
{
  //Open-Off, 5k-Deep, 0R-Light
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
    ModulationType = MODULATION_TYPE_DEEP;
  }
  //5V, using 0R and 10k
  else
  {
    ModulationType = MODULATION_TYPE_LIGHT;
  }
}
