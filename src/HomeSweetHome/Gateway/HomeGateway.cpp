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

	dht.UpdateTemperature();
	char string[16];
	sprintf(string, "%dC", dht.GetTemperature());

	lcd.WriteMessage(string, 1, 13);
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

	int index = -1;
	if ((index = espMessage.lastIndexOf("DT")) != -1)
	{
		String dateTimeString = espMessage.substring(index + 3);
		time.Set(dateTimeString.toInt());
		//time.Set(1494763605);

		String date, timing;
		time.Now(date, timing);
		lcd.WriteMessage(date, 0);
		lcd.WriteMessage(timing, 1);

		Serial.print("Time set to ");
		Serial.println(dateTimeString);
	}
}
