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
		ProcessMessage();

	if (dht.UpdateTemperature(espMessage))
		esp.SendMessage(espMessage);

	if (rfid.CheckForCard(espMessage))
		esp.SendMessage(espMessage);

	if (!door.IsDoorClosed(espMessage))
		esp.SendMessage(espMessage);


	delay(LOOP_DELAY);
}

void HomeGateway::ProcessMessage()
{
	Serial.print("Received: ");
	Serial.println(espMessage);
}
