#include "DHTController.h"

#define DHT11PIN 8
#define POLL_INTERVAL 60000

void DHTController::Initialize()
{
	lastRead = 0;

	Serial.print("DHTController initialized on pin ");
	Serial.println(DHT11PIN);

	Serial.print("DHT11 LIBRARY VERSION: ");
	Serial.println(DHT11LIB_VERSION);
}

bool DHTController::CheckForUpdate(String& message, bool force)
{
	if (millis() - lastRead > POLL_INTERVAL || force)
	{
		lastRead = millis();
		if (!UpdateTemperature())
			return false;

		char string[16];
		sprintf(string, "TP:%d:%d\t", DHT11.temperature, DHT11.humidity);

		message = string;

		return true;
	}

	return false;
}

bool DHTController::UpdateTemperature()
{
	int chk = DHT11.read(DHT11PIN);

	switch (chk)
	{
	case DHTLIB_OK:
		break;
	case DHTLIB_ERROR_CHECKSUM:
		Serial.println("DHTLIB_ERROR_CHECKSUM");
		return false;
	case DHTLIB_ERROR_TIMEOUT:
		Serial.println("DHTLIB_ERROR_TIMEOUT");
		return false;
	default:
		Serial.println("Unknown error");
		return false;
	}

	return true;
}
