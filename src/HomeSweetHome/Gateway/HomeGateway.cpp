#include "HomeGateway.h"

#define BAUD_RATE 74880
#define LOOP_DELAY 1

void HomeGateway::Initialize()
{
	Serial.begin(BAUD_RATE);

	esp.Initialize();
	rfid.Initialize();
	door.Initialize();
	dht.Initialize();
	lcd.Initialize();

	dht.UpdateTemperature();
	UpdateTemperature();
}

void HomeGateway::ExecuteLoop()
{
	if (esp.ReceiveMessage(espMessage))
		ProcessMessage();

	if (dht.CheckForUpdate(espMessage))
	{
		esp.SendMessage(espMessage);
		UpdateTemperature();
	}

	//if (rfid.CheckForCard(espMessage))
	//	esp.SendMessage(espMessage);

	//if (!door.IsDoorClosed(espMessage))
	//	esp.SendMessage(espMessage);

	if (time.Now(date, currentTime))
		UpdateTime();


	delay(LOOP_DELAY);
}

void HomeGateway::ProcessMessage()
{
	Serial.println(espMessage);

	int index = -1;
	if ((index = espMessage.lastIndexOf("DT")) != -1)
	{
		String dateTimeString = espMessage.substring(index + 3);
		time.Set(dateTimeString.toInt());
	}
}

void HomeGateway::UpdateTime()
{
	Serial.println(date);
	Serial.println(currentTime);

	lcd.WriteMessage(date, 0);
	lcd.WriteMessage(currentTime, 1);
}

void HomeGateway::UpdateTemperature()
{
	char string[4];
	sprintf(string, "%dC", dht.GetTemperature());

	Serial.print("Temperature is ");
	Serial.println(string);
	lcd.WriteMessage(string, 1, 13);
}
