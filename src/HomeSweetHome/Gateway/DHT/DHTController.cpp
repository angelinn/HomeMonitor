#include "DHTController.h"

#define DHT11PIN 8
#define POLL_INTERVAL 60000

void DHTController::Initialize()
{
	lastRead = 0;

	Serial.print("DHTController initialized on pin");
	Serial.print(DHT11PIN);

	Serial.print("DHT11 LIBRARY VERSION: ");
	Serial.println(DHT11LIB_VERSION);
}

bool DHTController::GetTemperature(int& temp, int& hum)
{
	if (millis() - lastRead > POLL_INTERVAL)
	{
		lastRead = millis();
		int chk = DHT11.read(DHT11PIN);

		switch (chk)
		{
		case DHTLIB_OK:
			break;
		case DHTLIB_ERROR_CHECKSUM:
			Serial.println("DHTLIB_ERROR_CHECKSUM");
			break;
		case DHTLIB_ERROR_TIMEOUT:
			Serial.println("DHTLIB_ERROR_TIMEOUT");
			break;
		default:
			Serial.println("Unknown error");
			break;
		}

		temp = DHT11.temperature;
		hum = DHT11.humidity;

		return true;
	}
	
	return false;
}
