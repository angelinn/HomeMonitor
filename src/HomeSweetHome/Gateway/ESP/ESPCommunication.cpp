#include "ESPCommunication.h"

#include <HardwareSerial.h>
#include <Arduino.h>

#define ESP_SERIAL Serial1
#define ESP_BAUD_RATE 9600
#define MESSAGE_DELIMITER '\t'

void ESPCommunication::Initialize()
{
	ESP_SERIAL.begin(ESP_BAUD_RATE);

	Serial.print("ESP8266 Initialized on Hardware Serial ");
	Serial.println(ESP_SERIAL);
}

void ESPCommunication::SendMessage(const String& message)
{
	ESP_SERIAL.print(message);
}

bool ESPCommunication::ReceiveMessage(String& message)
{
	if (ESP_SERIAL.available())
	{
		while (ESP_SERIAL.available())
			message = Serial1.readStringUntil(MESSAGE_DELIMITER);

		return true;
	}

	return false;
}

