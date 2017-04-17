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
	//rfid.Initialize();
	door.Initialize();
	dht.Initialize();
}

int temperature = 0;
int humidity = 0;

void loop() 
{
	esp.ReceiveMessage(espMessage);
	Serial.println(espMessage);

	dht.GetTemperature(temperature, humidity);
	char string[16];
	sprintf(string, "TP:%d:%d\t", temperature, humidity);
	Serial1.print(string);

	//rfid.CheckForCard();

	bool status = door.IsDoorClosed();
	Serial.println(status);


	delay(1000);
}