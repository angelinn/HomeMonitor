#include "DHTController.h"

#include <dht11.h>

dht11 DHT11;

#define DHT11PIN 8

void DHTController::Initialize()
{
	Serial.println("DHTController initialized.");
	Serial.print("LIBRARY VERSION: ");
	Serial.println(DHT11LIB_VERSION);
}

void DHTController::GetTemperature()
{
	int chk = DHT11.read(DHT11PIN);

	Serial.print("Read sensor: ");
	switch (chk)
	{
	case DHTLIB_OK:
	Serial.println("OK");
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

	Serial.print("Humidity (%): ");
	Serial.println((float)DHT11.humidity, 2);

	Serial.print("Temperature (°C): ");
	Serial.println((float)DHT11.temperature, 2);
	
}
