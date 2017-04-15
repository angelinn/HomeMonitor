#include "ESPCommunication.h"

void ESPCommunication::Initialize()
{
	Serial1.begin(9600);
	Serial.println("ESP8266 Initialized");
}

void ESPCommunication::SendMessage(const char* message)
{
	Serial1.write(message);

	Serial.print("Written ");
	Serial.println(message);
}

void ESPCommunication::ReceiveMessage(String& message)
{
	while (Serial1.available())
	{
		message = Serial1.readString();
		// Debug
		Serial.println(message);
	}
}