#include "RFIDController.h"

#include <SPI.h>

#define SS_PIN 10
#define RST_PIN 9

RFIDController::RFIDController(): mfrc(SS_PIN, RST_PIN)
{   }

void RFIDController::Initialize()
{
	SPI.begin();			// Init SPI bus
	mfrc.PCD_Init();	// Init MFRC522 card

	Serial.println("RFIDController initialized.");
}

void RFIDController::CheckForCard()
{
	if (!mfrc.PICC_IsNewCardPresent())
		return;

	// Select one of the cards
	if (!mfrc.PICC_ReadCardSerial())
		return;//if ReadCardSerial returns 1, the "uid" struct (see MFRC522.h lines 238-45)) contains the ID of the read card.

	// Dump debug info about the card. PICC_HaltA() is automatically called.
	mfrc.PICC_DumpToSerial(&(mfrc.uid));
}
