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
	lcd.Initialize();

	lcd.WriteMessage("01 May 2017", 0);
	dht.UpdateTemperature();
	char string[16];
	sprintf(string, "%dC", dht.GetTemperature());

	lcd.WriteMessage(string, 1, 13);
	lcd.WriteMessage("19:35", 1);

}

void HomeGateway::ExecuteLoop()
{
	if (esp.ReceiveMessage(espMessage))
		ProcessMessage();

	if (dht.CheckForUpdate(espMessage))
	{
		esp.SendMessage(espMessage);

		char string[16];
		sprintf(string, "%dC", dht.GetTemperature());

		lcd.WriteMessage(string, 1, 13);
	}

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
