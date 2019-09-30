#include "Arduino.h"

class EepromManager
{
	public:
		EepromManager(void);
		void Initialise(void);
		uint8_t Read(uint8_t address);
		void Write(uint8_t address, uint8_t value);
};