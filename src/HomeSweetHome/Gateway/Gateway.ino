#include "RFID\RFIDController.h"

RFIDController rfid;

void setup() 
{
	Serial.begin(9600);	// Initialize serial communications with the PC

	
	rfid.Initialize();
}

void loop() 
{
	rfid.CheckForCard();
}