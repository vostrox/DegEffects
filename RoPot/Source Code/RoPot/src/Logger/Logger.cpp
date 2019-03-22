#include "Arduino.h"
#include "Logger.h"

const int BaudRate = 31250;

Logger::Logger(void)
{
  
}

Logger::~Logger(void)
{
  if (Serial)
  {
    Serial.flush();
    Serial.end();
  }
}

void Logger::Initialise(bool enabled)
{
  _enabled = enabled;

  if (_enabled && Serial)
  {
    Serial.begin(BaudRate);
    while(!Serial);
  }
}

void Logger::Error(String message)
{
  if (_enabled && Serial)
  {
    Serial.println("Error: " + message);
  }
}

void Logger::Warning(String message)
{
  if (_enabled && Serial)
  {
    Serial.println("Warning: " + message);
  }
}

void Logger::Info(String message)
{
  if (_enabled && Serial)
  {
    Serial.println("Info: " + message);
  }
}
