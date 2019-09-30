#include "EepromManager.h"
#include <EEPROM.h>

EepromManager::EepromManager(void)
{
	
}

void EepromManager::Initialise(void)
{

}

uint8_t EepromManager::Read(uint8_t address)
{
	return EEPROM.read(address);
}
void EepromManager::Write(uint8_t address, uint8_t value)
{
	EEPROM.update(address, value);
}