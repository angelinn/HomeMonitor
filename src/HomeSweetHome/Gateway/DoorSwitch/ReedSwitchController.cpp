#include "ReedSwitchController.h"

#include <Arduino.h>

#define REED_PIN 36

void ReedSwitchController::Initialize()
{
	pinMode(REED_PIN, INPUT);

	Serial.print("ReedSwitchController initialized on pin ");
	Serial.println(REED_PIN);
}

bool ReedSwitchController::IsDoorClosed()
{
	return digitalRead(REED_PIN);
}
