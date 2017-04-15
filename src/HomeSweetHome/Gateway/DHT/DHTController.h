#pragma once

#include <dht11.h>

class DHTController
{
public:
	void Initialize();
	void GetTemperature(int &, int &);

private:
	dht11 DHT11;
};