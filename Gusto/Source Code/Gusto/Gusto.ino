#include <SPI.h>
#include "TimerOne.h"

#define PIN_TAP 2
#define PIN_LED_RED 4
#define PIN_LED_GREEN 5
#define PIN_LED_BLUE 6
#define PIN_TIME_KNOB PIN_A0
#define PIN_SUBDIVISION PIN_A1
#define PIN_MODULATION_TYPE PIN_A2
#define PIN_SPI_SLAVESELECT 10
#define PIN_SPI_CHIPMODE 7

#define TIME_MINIMUM_DELAY_MILLISECONDS 40
#define TIME_MAXIMUM_DELAY_MILLISECONDS 1116
#define TIME_DEBOUNCE_WAIT_MILLISECONDS 200
#define TIME_TAP_RESET_MILLISECONDS 5000
#define TIME_TIMER_SAMPLE_DELAY_MICROSECONDS 20000
#define TIME_LED_ON_MILLISECONDS 30
#define TIME_DEFAULT_DELAY_MILLISECONDS 500

#define SUBDIVISION_QUARTER 0
#define SUBDIVISION_DOTTEDEIGHTHS 1
#define SUBDIVISION_EIGHTHS 2

#define MODULATION_TYPE_OFF 0
#define MODULATION_TYPE_LIGHT 1
#define MODULATION_TYPE_DEEP 2
#define MODULATION_DEPTH_LIGHT 2.0
#define MODULATION_DEPTH_DEEP 3.0
#define MODULATION_SPEED_LIGHT 1.0
#define MODULATION_SPEED_DEEP 1.5

double TempoMs = TIME_DEFAULT_DELAY_MILLISECONDS;
int ModulationType = MODULATION_TYPE_OFF;
int SubDivision = SUBDIVISION_QUARTER;

void setup()
{
  //Serial.begin(115200);
  //while (!Serial);

  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(PIN_SPI_SLAVESELECT, OUTPUT);
  pinMode(PIN_SPI_CHIPMODE, OUTPUT);
  
  pinMode(PIN_TAP, INPUT);

  //InitialiseMidi();
  
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);

  CheckTimeKnob();
  CheckSubDivisionSwitch();
  CheckModulationSwitch();
  
  Timer1.initialize(TIME_TIMER_SAMPLE_DELAY_MICROSECONDS);
  Timer1.attachInterrupt(Modulate);
  
  attachInterrupt(digitalPinToInterrupt(PIN_TAP), TapPressed, RISING);

  digitalWrite(PIN_SPI_CHIPMODE, HIGH);
  
  //Serial.println("Finished setup");
}

void loop()
{
  //CheckMidi();
  FlashLED();
  
  delay(TempoMs - TIME_LED_ON_MILLISECONDS);
}
