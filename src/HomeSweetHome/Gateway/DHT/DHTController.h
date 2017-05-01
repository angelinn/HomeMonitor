#pragma once

#include <dht11.h>

class DHTController
{
public:
	void Initialize();
	bool UpdateTemperature();

public:
	int GetTemperature() { return DHT11.temperature; }
	int GetHumidity() { return DHT11.humidity; }

private:
	dht11 DHT11;
	unsigned long lastRead;

	int temperature;
	int humidity;
};