#include "HomeGateway.h"

HomeGateway gateway;

void setup()
{
	gateway.Initialize();
}

void loop()
{
	gateway.ExecuteLoop();
}