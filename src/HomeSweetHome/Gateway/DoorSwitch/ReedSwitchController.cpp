#include "ReedSwitchController.h"

#include <Arduino.h>

#define REED_PIN 36

void ReedSwitchController::Initialize()
{
	pinMode(REED_PIN, INPUT);

	Serial.print("ReedSwitchController initialized on pin ");
	Serial.println(REED_PIN);
}

bool ReedSwitchController::IsDoorClosed(String& message)
{
	int read = digitalRead(REED_PIN);
	if (!read)
		Serial.println("Door is open.");

	message = "RS:" + read;
	return read;
}
