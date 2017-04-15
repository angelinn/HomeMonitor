#include "ESPCommunication.h"

#include <HardwareSerial.h>
#include <Arduino.h>

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

int ESPCommunication::ReceiveMessage()
{
	while (Serial1.available())
	{
		Serial.println("readin'");
		Serial.println(Serial1.readStringUntil('\t'));
		//int code = Serial1.read();
		//Serial.println(code);
		return 1;
	}
}

