#include "ESPCommunication.h"

#include <HardwareSerial.h>
#include <Arduino.h>

#define ESP_SERIAL Serial1

void ESPCommunication::Initialize()
{
	ESP_SERIAL.begin(9600);
	Serial.print("ESP8266 Initialized on Hardware Serial ");
	Serial.println(ESP_SERIAL);
}

void ESPCommunication::SendMessage(const char* message)
{
	ESP_SERIAL.write(message);
}

bool ESPCommunication::ReceiveMessage(String& message)
{
	if (ESP_SERIAL.available())
	{
		while (ESP_SERIAL.available())
			message = Serial1.readStringUntil('\t');

		return true;
	}

	return false;
}

