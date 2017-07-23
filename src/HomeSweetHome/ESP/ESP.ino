#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include "Connection\HttpConnection.h"

#define KEY_BEGIN 0
#define KEY_END 2
#define VALUE_BEGIN 3
#define DELIMITER '\t'
#define HEARTBEAT_INTERVAL 30000
#define SSID "The Pepper"
#define PASSWORD "95827572580"

ConnectionProvider* client = nullptr;
ESP8266WiFiMulti WiFiMulti;

unsigned long lastHeartbeat = millis();

void setup()
{
	Serial.begin(74880);

	initializeWifi();

	client = new HttpConnection(&WiFiMulti);
	String time = client->requestTime();

	char buffer[32];
	sprintf(buffer, "DT:%s\t", time.c_str());
	Serial.print(buffer);

	heartbeat();
}

void initializeWifi()
{
	Serial.print("Connecting to ");
	Serial.println(SSID);

	for (uint8_t t = 4; t > 0; t--) 
	{
		Serial.printf("[SETUP] WAIT %d...\t", t);
		Serial.flush();
		delay(1000);
	}

	WiFiMulti.addAP(SSID, PASSWORD);
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
}

void processCommand(const String& command)
{
	Serial.printf("RECEIVED %s\t", command.c_str());
	String key = command.substring(KEY_BEGIN, KEY_END);
	String value = command.substring(VALUE_BEGIN);

	Serial.printf("GOT %s\t", key.c_str());
	Serial.printf("GOT VALUE %s\t", value.c_str());

	if (key == "TP")
	{
		String params[] = { value.substring(0, 2), value.substring(3, 5) };
		client->sendWeatherData(params);
	}
	else if (key == "RS")
	{
		client->sendDoorData(value);
	}
	else if (key == "MV")
	{
		client->sendMoveData();
	}
}

void loop()
{
	while (Serial.available())
		processCommand(Serial.readStringUntil(DELIMITER));

	if (millis() - lastHeartbeat > HEARTBEAT_INTERVAL)
	{
		heartbeat();
		lastHeartbeat = millis();
	}
	delay(1000);
}

void heartbeat()
{
	client->heartbeat();
	Serial.write("HEARTBEAT\t");
}
