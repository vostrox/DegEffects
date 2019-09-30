volatile double _previousTapTime = 0;

void TapPressed()
{  
  noInterrupts();
  
  double newTime = millis();
  double tempMs = newTime - _previousTapTime;

  if (tempMs > TIME_TAP_RESET_MILLISECONDS)
  {
    _previousTapTime = newTime;
  }
  else if (tempMs >= TIME_DEBOUNCE_WAIT_MILLISECONDS)
  {
    _previousTapTime = newTime;
    
    if (tempMs >= TIME_MINIMUM_DELAY_MILLISECONDS && tempMs <= TIME_MAXIMUM_DELAY_MILLISECONDS)
    {
      TempoMs = tempMs;
    }
  }
  
  interrupts();
}

void Modulate()
{
  CheckTimeKnob();
  CheckSubDivisionSwitch();
  CheckModulationSwitch();
  
  double modDepth = 0;
  double modSpeed = 0;
  
  switch (ModulationType)
  {
    case MODULATION_TYPE_OFF:
      UpdateWiperPosition(0);
      return;
    case MODULATION_TYPE_LIGHT:
	    modDepth = MODULATION_DEPTH_LIGHT;
      modSpeed = MODULATION_SPEED_LIGHT;
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
