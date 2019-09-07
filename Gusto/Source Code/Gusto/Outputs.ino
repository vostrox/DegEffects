#define MODULATION_ERROR_CORRECTION 0.5
#define MAXIMUM_WIPER_VALUE 1023

void FlashLED()
{
  //TAP ON STATE (primary colours)
  //RGB - White   - Quarter
  //R   - Red     - Eighth
  //G   - Green   - Dotted Eighth
  //B   - Blue    - MIDI changes to tap
  
  auto redOn = LOW;
  auto greenOn = LOW;
  auto blueOn = LOW;

  if (SubDivision == SUBDIVISION_QUARTER)
  {
    redOn = HIGH;
	  greenOn = HIGH;
	  blueOn = HIGH;
  }
  else if (SubDivision == SUBDIVISION_EIGHTHS)
  {
    redOn = HIGH;
  }
  else if (SubDivision == SUBDIVISION_DOTTEDEIGHTHS)
  {
    greenOn = HIGH;
  }

  digitalWrite(PIN_LED_RED, redOn);
  digitalWrite(PIN_LED_GREEN, greenOn);
  digitalWrite(PIN_LED_BLUE, blueOn);
  
  delay(TIME_LED_ON_MILLISECONDS);

  //TAP OFF STATE (secondary colours)
  //	  - Black	  - No mod
  //RB  - Magenta - Deep mod
  //GB  - Cyan    - Light mod
  //RG	- Yellow  - MIDI changes to mod
  
  redOn = LOW;
  greenOn = LOW;
  blueOn = LOW;
  
  if (ModulationType == MODULATION_TYPE_OFF)
  {
    //keep all LEDs low
  }
  else if (ModulationType == MODULATION_TYPE_LIGHT)
  {
    greenOn = HIGH;
	  blueOn = HIGH;
  }
  else if (ModulationType == MODULATION_TYPE_DEEP)
  {
    redOn = HIGH;
	  blueOn = HIGH;
  }
  
  digitalWrite(PIN_LED_RED, redOn);
  digitalWrite(PIN_LED_GREEN, greenOn);
  digitalWrite(PIN_LED_BLUE, blueOn);
}

void UpdateWiperPosition(double mod)
{
  noInterrupts();
  
  double delayMs = TempoMs;
  
  //calculate delayMs from tempoMs and subDivision
  if (SubDivision == SUBDIVISION_EIGHTHS)
  {
    delayMs = TempoMs / 2;
  }      
  else if (SubDivision == SUBDIVISION_DOTTEDEIGHTHS)
  {
    delayMs = TempoMs * 0.75;
  }

  delayMs = delayMs + mod + MODULATION_ERROR_CORRECTION;
  
  if (delayMs < TIME_MINIMUM_DELAY_MILLISECONDS)
  {
    delayMs = TIME_MINIMUM_DELAY_MILLISECONDS;
  }
  else if (delayMs > TIME_MAXIMUM_DELAY_MILLISECONDS)
  {
    delayMs = TIME_MAXIMUM_DELAY_MILLISECONDS;
  }
  
  unsigned int wiperValue = ((delayMs - TIME_MINIMUM_DELAY_MILLISECONDS) / (TIME_MAXIMUM_DELAY_MILLISECONDS - TIME_MINIMUM_DELAY_MILLISECONDS)) * MAXIMUM_WIPER_VALUE;
  wiperValue = constrain(wiperValue, 0, MAXIMUM_WIPER_VALUE);
    
  //  we need to investigate the relationship between the wiper position and the delay time
  //  is the delay time directly proportional to the wiper position?
  //  do we need to invert the value?

  //https://forum.arduino.cc/index.php?topic=242376.0
  //https://uk.rs-online.com/web/p/digital-potentiometers/7329711/
  //MAX5481EUD+
  digitalWrite(PIN_SPI_SLAVESELECT, LOW);
  SPI.transfer(0x00);
  SPI.transfer(highByte(wiperValue<<6));
  SPI.transfer(lowByte(wiperValue<<6));
  digitalWrite(PIN_SPI_SLAVESELECT, HIGH);

  interrupts();
}
