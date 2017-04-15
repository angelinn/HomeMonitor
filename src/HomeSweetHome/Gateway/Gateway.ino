#include "RFID\RFIDController.h"
#include "ESP\ESPCommunication.h"
#include "DHT\DHTController.h"

RFIDController rfid;
ESPCommunication esp;
DHTController dht;

String espMessage = "";

void setup() 
{
	Serial.begin(9600);	// Initialize serial communications with the PC
	
	//rfid.Initialize();
	dht.Initialize();
	esp.Initialize();
}

void loop() 
{
	dht.GetTemperature();

	esp.ReceiveMessage(espMessage);
	Serial.println(espMessage);
	//rfid.CheckForCard();

	delay(1000);
}