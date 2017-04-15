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
	String message = "";
	esp.ReceiveMessage(message);
	//rfid.CheckForCard();
}