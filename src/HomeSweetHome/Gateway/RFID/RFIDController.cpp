#include "RFIDController.h"

#include <SPI.h>

#define SS_PIN 10
#define RST_PIN 11

RFIDController::RFIDController(): mfrc(SS_PIN, RST_PIN)
{   }

void RFIDController::Initialize()
{
	SPI.begin();			// Init SPI bus
	mfrc.PCD_Init();	// Init MFRC522 card

	char message[256];
	sprintf(message, "RFIDController initialized on pins: SS: %d, MOSI %d, MISO %d, SCK %d", SS_PIN, MOSI, MISO, SCK);
	Serial.println(message);
}

bool RFIDController::CheckForCard(String& uid)
{
	if (!mfrc.PICC_IsNewCardPresent())
		return;

	// Select one of the cards
	if (!mfrc.PICC_ReadCardSerial())
		return;//if ReadCardSerial returns 1, the "uid" struct (see MFRC522.h lines 238-45)) contains the ID of the read card.

	// Dump debug info about the card. PICC_HaltA() is automatically called.
	// mfrc.PICC_DumpToSerial(&(mfrc.uid));

	Serial.print("Card UID:");
	uid = "RF:";

	for (byte i = 0; i < mfrc.uid.size; i++) 
	{
		uid += mfrc.uid.uidByte[i] < 0x10 ? " 0" : " ";
		uid += mfrc.uid.uidByte[i];
	}
	Serial.println(uid);

	return uid;
}
