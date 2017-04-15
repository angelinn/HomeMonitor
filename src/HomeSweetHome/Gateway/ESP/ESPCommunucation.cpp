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

void ESPCommunication::ReceiveMessage(String& message)
{
	while (Serial1.available())
		message = Serial1.readStringUntil('\t');
}

