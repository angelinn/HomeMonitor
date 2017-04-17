#pragma once

#include <dht11.h>

class DHTController
{
	typedef unsigned time_t;

public:
	void Initialize();
	bool GetTemperature(int &, int &);

private:
	dht11 DHT11;
	time_t lastRead;
};