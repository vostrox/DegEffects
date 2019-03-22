#include "Arduino.h"

class Logger
{
  public:
    Logger();
    ~Logger();
    void Initialise(bool enabled);
    void Error(String message);
    void Warning(String message);
    void Info(String message);
  private:
    bool _enabled;
};

