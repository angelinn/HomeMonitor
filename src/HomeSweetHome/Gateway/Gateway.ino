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

	delay(1000);
}