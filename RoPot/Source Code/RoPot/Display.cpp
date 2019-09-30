#include "Display.h"
#include "src/Logger/Logger.h"
#include <Wire.h>

bool zero[8][5] =
{
	{0,0,0,0,0},
	{0,1,1,1,0},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{0,1,1,1,0}
};

bool one[8][5] =
{
	{0,0,0,0,0},
	{0,0,1,0,0},
	{0,1,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{1,1,1,1,1}
};

bool two[8][5] =
{
	{0,0,0,0,0},
	{0,1,1,1,0},
	{1,0,0,0,1},
	{0,0,0,1,0},
	{0,0,1,0,0},
	{0,1,0,0,0},
	{1,0,0,0,0},
	{1,1,1,1,1}
};

bool three[8][5] =
{
	{0,0,0,0,0},
	{1,1,1,1,0},
	{0,0,0,0,1},
	{0,0,0,0,1},
	{0,1,1,1,0},
	{0,0,0,0,1},
	{0,0,0,0,1},
	{1,1,1,1,0}
};

bool four[8][5] =
{
	{0,0,0,0,0},
	{0,0,0,1,0},
	{0,0,1,1,0},
	{0,1,0,1,0},
	{0,1,0,1,0},
	{1,0,0,1,0},
	{1,1,1,1,1},
	{0,0,0,1,0}
};

bool five[8][5] =
{
	{0,0,0,0,0},
	{1,1,1,1,1},
	{1,0,0,0,0},
	{1,1,1,1,0},
	{1,0,0,0,1},
	{0,0,0,0,1},
	{1,0,0,0,1},
	{0,1,1,1,0}
};

bool six[8][5] =
{
	{0,0,0,0,0},
	{0,1,1,1,0},
	{1,0,0,0,1},
	{1,0,0,0,0},
	{1,1,1,1,0},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{0,1,1,1,0}
};

bool seven[8][5] =
{
	{0,0,0,0,0},
	{1,1,1,1,1},
	{0,0,0,0,1},
	{0,0,0,1,0},
	{0,0,0,1,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0}
};

bool eight[8][5] =
{
	{0,0,0,0,0},
	{0,1,1,1,0},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{0,1,1,1,0},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{0,1,1,1,0}
};

bool nine[8][5] =
{
	{0,0,0,0,0},
	{0,1,1,1,0},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{0,1,1,1,1},
	{0,0,0,0,1},
	{1,0,0,0,1},
	{0,1,1,1,0}
};

Logger _logger;

Display::Display(void)
{
	
}

void Display::Initialise(void)
{
	_logger.Initialise(true);

	Wire.begin();
	
	Wire.beginTransmission(HT16K33_I2C_ADDRESS);
	
	// Turn on the oscillator
	Wire.write(0x21);
	Wire.endTransmission();
	BlinkRate(HT16K33_BLINK_OFF);
	
	// Max brightness
	SetBrightness(1);
}

void Display::DisplayPreset(uint8_t value, uint8_t presetId)
{
	bool presetMatrix[8][5];

	switch (presetId)
	{
		case 0:
		{
			CopyMatrix(zero, presetMatrix);
			break;
		}
		case 1:
		{
			CopyMatrix(one, presetMatrix);
			break;
		}
		case 2:
		{
			CopyMatrix(two, presetMatrix);
			break;
		}
		case 3:
		{
			CopyMatrix(three, presetMatrix);
			break;
		}
		case 4:
		{
			CopyMatrix(four, presetMatrix);
			break;
		}
		case 5:
		{
			CopyMatrix(five, presetMatrix);
			break;
		}
		case 6:
		{
			CopyMatrix(six, presetMatrix);
			break;
		}
		case 7:
		{
			CopyMatrix(seven, presetMatrix);
			break;
		}
		case 8:
		{
			CopyMatrix(eight, presetMatrix);
			break;
		}
		case 9:
		{
			CopyMatrix(nine, presetMatrix);
			break;
		}
		default:
		{
			CopyMatrix(zero, presetMatrix);
			break;
		}
	}

	// Convert the value from range 0-127 to 0-7
	uint8_t barValue = round((9 * value) / 127);
  _logger.Info(String(barValue, DEC));
	// Flip bar value so that 7 lights up all rows down to 0 not lighting any
	barValue = 8 - barValue;

  bool outputMatrix[8][8];

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (x < 2)
			{
				if (barValue >= y)
				{
					//outputMatrix[y][x] = barValue;
          outputMatrix[y][x] = 0;
				}
				else
				{
					outputMatrix[y][x] = 1;
				}
			}
			else if (x == 2)
			{
				outputMatrix[y][x] = 0;
			}
			else
			{
				outputMatrix[y][x] = presetMatrix[y][x - 3];
			}
		}
	}

	DrawMatrix(outputMatrix);
}

void Display::DisplayContinuousMode(uint8_t value)
{
	// Convert the value from range 0-127 to 0-7
	uint8_t barValue = round((7 * value) / 127);

	// Flip bar value so that 7 lights up all rows down to 0 not lighting any
	barValue = 7 - barValue;

	bool outputMatrix[8][8];

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (barValue >= y)
			{
				outputMatrix[y][x] = barValue;
			}
			else
			{
				outputMatrix[y][x] = 0;
			}
		}
	}

	DrawMatrix(outputMatrix);
}

void Display::SetPixel(int16_t x, int16_t y, bool enabled)
{
	if ((x < 0) || (x >= 8) || (y < 0) || (y >= 8))
	{
		return;
	}

	// Wrap around the x
	x += 7;
	x %= 8;

	if (enabled)
	{
		_displayBuffer[y] |= 1 << x;
	}
	else
	{
		_displayBuffer[y] &= ~(1 << x);
	}
}

void Display::WriteDisplay(void)
{
	Wire.beginTransmission(HT16K33_I2C_ADDRESS);

	// Start at address $00
	Wire.write((uint8_t)0x00);

	for (uint8_t i = 0; i < 8; i++)
	{
		Wire.write(_displayBuffer[i] & 0xFF);
		Wire.write(_displayBuffer[i] >> 8);
	}
	Wire.endTransmission();
}

void Display::DrawMatrix(bool matrix[8][8])
{
	for (uint8_t y = 0; y < 8; y++)
	{
		for (uint8_t x = 0; x < 8; x++)
		{
			SetPixel(x, y, matrix[y][x]);
		}
	}

	WriteDisplay();
	
	// Clear the buffer
	for (uint8_t i = 0; i < 8; i++)
	{
		_displayBuffer[i] = 0;
	}
}

void Display::SetBrightness(uint8_t b)
{
	if (b > 15)
	{
		b = 15;
	}
	
	Wire.beginTransmission(HT16K33_I2C_ADDRESS);
	Wire.write(HT16K33_CMD_BRIGHTNESS | b);
	Wire.endTransmission();
}

void Display::BlinkRate(uint8_t b)
{
	Wire.beginTransmission(HT16K33_I2C_ADDRESS);
	
	if (b > 3)
	{
		b = 0;
	}
	
	Wire.write(HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (b << 1)); 
	Wire.endTransmission();
}

void Display::CopyMatrix(bool source[8][5], bool destination[8][5])
{
	for (uint8_t i = 0; i < 8; i++)
	{
		for (uint8_t j = 0; j < 5; j++)
		{
			destination[i][j] = source[i][j];
		}
	}
}
