#include "LCDController.h"
#include "Arduino.h"

#define RS 28
#define RW 27
#define ENABLE 26
#define D4 25
#define D5 24
#define D6 23
#define D7 22
#define BACKLIGHT 12

#define START_BRIGHTNESS 255
#define ROWS 16
#define COLS 2

LCDController::LCDController() : lcd(RS, RW, ENABLE, D4, D5, D6, D7)
{

}

void LCDController::Initialize()
{
	analogWrite(BACKLIGHT, START_BRIGHTNESS);

	lcd.begin(ROWS, COLS);
	lcd.clear();
}

void LCDController::WriteMessage(const String& message, uint8_t row, uint8_t cursor)
{
	lcd.setCursor(cursor, row);
	lcd.print(message);
}
