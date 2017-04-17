#include "RFID\RFIDController.h"
#include "ESP\ESPCommunication.h"
#include "DHT\DHTController.h"
#include "DoorSwitch\ReedSwitchController.h"

RFIDController rfid;
ESPCommunication esp;
DHTController dht;
ReedSwitchController door;

String espMessage = "";

void setup()
{
	Serial.begin(9600);

	esp.Initialize();
	rfid.Initialize();
	door.Initialize();
	dht.Initialize();
}

int temperature = 0;
int humidity = 0;

void loop()
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


	delay(1000);
}