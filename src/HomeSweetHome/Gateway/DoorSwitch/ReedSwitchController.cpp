#include "ReedSwitchController.h"

#include <Arduino.h>

#define REED_PIN 36
#define buzzer 3

bool keepOn = true;

void beep()
{
	unsigned char i, j;// define variables

	for (i = 0; i < 80; i++)
	{
		digitalWrite(buzzer, LOW); // Turn buzzer ON
		delay(1);// Delay 1ms
		digitalWrite(buzzer, HIGH);// turn buzzer OFF
		delay(1);// delay ms
	}
	for (i = 0; i < 100; i++) // new frequency
	{
		digitalWrite(buzzer, LOW);// turn buzzer ON
		delay(2);// delay 2ms
		digitalWrite(buzzer, HIGH);// turn buzzer OFF
		delay(2);// delay 2ms
	}
}

void ReedSwitchController::Initialize()
{
	pinMode(REED_PIN, INPUT);
	pinMode(3, OUTPUT);

	Serial.print("ReedSwitchController initialized on pin ");
	Serial.println(REED_PIN);
}

bool ReedSwitchController::IsDoorClosed(String& message)
{
	int read = digitalRead(REED_PIN);
	if (!read)
	{
		Serial.println("Door is open.");

		beep();
	}

	message = "RS:" + read;
	return read;
}
