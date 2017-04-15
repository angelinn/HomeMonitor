#include "DHTController.h"

#define DHT11PIN 8

void DHTController::Initialize()
{
	Serial.println("DHTController initialized.");
	Serial.print("LIBRARY VERSION: ");
	Serial.println(DHT11LIB_VERSION);
}

void DHTController::GetTemperature(int& temp, int& hum)
{
	int chk = DHT11.read(DHT11PIN);

	switch (chk)
	{
	case DHTLIB_OK:
	break;
	case DHTLIB_ERROR_CHECKSUM:
	Serial.println("Checksum error");
	break;
	case DHTLIB_ERROR_TIMEOUT:
	Serial.println("Time out error");
	break;
	default:
	Serial.println("Unknown error");
	break;
	}

	temp = DHT11.temperature;
	hum = DHT11.humidity;
}
