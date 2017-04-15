#include "RFID\RFIDController.h"
#include "ESP\ESPCommunication.h"

RFIDController rfid;
ESPCommunication esp;

void setup() 
{
	Serial.begin(9600);	// Initialize serial communications with the PC
	
	//rfid.Initialize();
	esp.Initialize();
}

void loop() 
{
	esp.ReceiveMessage();
	//rfid.CheckForCard();

	delay(1000);
}