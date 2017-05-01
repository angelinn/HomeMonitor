#include "HomeGateway.h"

#define BAUD_RATE 9600
#define LOOP_DELAY 1000

void HomeGateway::Initialize()
{
	Serial.begin(BAUD_RATE);

	esp.Initialize();
	rfid.Initialize();
	door.Initialize();
	dht.Initialize();
}

void HomeGateway::ExecuteLoop()
{
	if (esp.ReceiveMessage(espMessage))
	{
		Serial.print("Received: ");
		Serial.println(espMessage);
	}

	if (dht.GetTemperature(temperature, humidity))
	{
		char string[16];
		sprintf(string, "TP:%d:%d\t", temperature, humidity);
		esp.SendMessage(string);
	}
	rfid.CheckForCard();

	bool status = door.IsDoorClosed();
	if (!status)
		Serial.println("Door is open.");


	delay(LOOP_DELAY);
}
