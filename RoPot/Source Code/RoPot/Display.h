#include "Arduino.h"

#define HT16K33_I2C_ADDRESS 0x70

#define HT16K33_BLINK_CMD 0x80
#define HT16K33_BLINK_DISPLAYON 0x01
#define HT16K33_BLINK_OFF 0
#define HT16K33_CMD_BRIGHTNESS 0xE0

class Display
{
	public:
		Display(void);
		void Initialise(void);
		void DisplayPreset(uint8_t value, uint8_t presetId);
		void DisplayContinuousMode(uint8_t value);

	private:
		void SetPixel(int16_t x, int16_t y, bool enabled);
		void WriteDisplay(void);
		void DrawMatrix(bool matrix[8][8]);
		void SetBrightness(uint8_t b);
		void BlinkRate(uint8_t b);
		void CopyMatrix(bool source[8][5], bool destination[8][5]);
		uint16_t _displayBuffer[8];
};
