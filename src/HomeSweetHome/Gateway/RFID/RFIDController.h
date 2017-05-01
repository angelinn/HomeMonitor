/*
* MFRC522 - Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W AND R BY COOQROBOT.
* The library file MFRC522.h has a wealth of useful info. Please read it.
* The functions are documented in MFRC522.cpp.
*
* Based on code Dr.Leong   ( WWW.B2CQSHOP.COM )
* Created by Miguel Balboa (circuitito.com), Jan, 2012.
* Rewritten by Søren Thing Andersen (access.thing.dk), fall of 2013 (Translation to English, refactored, comments, anti collision, cascade levels.)
* Released into the public domain.
*
* Sample program showing how to read data from a PICC using a MFRC522 reader on the Arduino SPI interface.
*----------------------------------------------------------------------------- empty_skull
* Aggiunti pin per arduino Mega
* add pin configuration for arduino mega
* http://mac86project.altervista.org/
----------------------------------------------------------------------------- Nicola Coppola
* Pin layout should be as follows:
* Signal     Pin              Pin               Pin
*            Arduino Uno      Arduino Mega      MFRC522 board
* ------------------------------------------------------------
* Reset      9                5                 RST
* SPI SS     10               53                SDA
* SPI MOSI   11               52                MOSI
* SPI MISO   12               51                MISO
* SPI SCK    13               50                SCK
*
* The reader can be found on eBay for around 5 dollars. Search for "mf-rc522" on ebay.com.
*/

#pragma once

#include <MFRC522.h>

class RFIDController
{
public:
	RFIDController();

public:
	void Initialize();
	bool CheckForCard(String &);

private:
	MFRC522 mfrc;
};