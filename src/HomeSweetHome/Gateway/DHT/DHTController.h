#pragma once

#include <dht11.h>

class DHTController
{
public:
	void Initialize();
	bool GetTemperature(int &, int &);

private:
	dht11 DHT11;
	unsigned long lastRead;
};