#pragma once

#include <LiquidCrystal.h>

class LCDController
{
public:
	LCDController();

public:
	void Initialize();
	void WriteMessage(const String &, uint8_t);

private:
	LiquidCrystal lcd;
};
