volatile double previousTapTime = 0;

void TapPressed()
{  
  double newTime = millis();
  double tempMs = newTime - previousTapTime;

  if (tempMs > TIME_TAP_RESET_MILLISECONDS)
  {
    previousTapTime = newTime;
  }
  else if (tempMs >= TIME_DEBOUNCE_WAIT_MILLISECONDS)
  {
    previousTapTime = newTime;

    if (tempMs >= TIME_MINIMUM_DELAY_MILLISECONDS && tempMs <= TIME_MAXIMUM_DELAY_MILLISECONDS)
    {
      TempoMs = tempMs;
    }
  }
}

void Modulate()
{
  CheckTimeKnob();
  CheckSubDivisionSwitch();
  CheckModulationSwitch();
  
  double modDepth = MODULATION_DEPTH_LIGHT;
  double modSpeed = MODULATION_SPEED_LIGHT;
  
  switch (ModulationType)
  {
    case MODULATION_TYPE_OFF:
      UpdateWiperPosition(0);
      return;
    case MODULATION_TYPE_LIGHT:
      break;
    case MODULATION_TYPE_DEEP:
      modDepth = MODULATION_DEPTH_DEEP;
      modSpeed = MODULATION_SPEED_DEEP;  
      break;
  }

  double timeSeconds = millis() / 1000.0;
  double mod = (modDepth / 2.0) * sin(2.0 * PI * modSpeed * timeSeconds);
  
  UpdateWiperPosition(mod);
}
