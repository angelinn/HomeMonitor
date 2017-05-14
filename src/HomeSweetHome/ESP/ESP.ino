#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>

#include <ESP8266HTTPClient.h>

#define KEY_BEGIN 0
#define KEY_END 2
#define VALUE_BEGIN 3
#define DELIMITER '\t'
#define HEARTBEAT_INTERVAL 30000
#define SSID "The Pepper"
#define PASSWORD "9582757280"

ESP8266WiFiMulti WiFiMulti;

unsigned long lastHeartbeat = millis();

void setup()
{
	Serial.begin(9600);
	
	Serial.print("Connecting to ");
	Serial.println(SSID);

	for (uint8_t t = 4; t > 0; t--) {
		Serial.printf("[SETUP] WAIT %d...\n", t);
		Serial.flush();
		delay(1000);
	}
	WiFiMulti.addAP(SSID, PASSWORD);
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());

	String time = sendRequest("http://192.168.0.103:55155/api/time");
	char buffer[32];
	sprintf(buffer, "DT:%s\t", time.c_str());
	Serial.print(buffer);

	sendRequest("http://192.168.0.103:55155/api/events?eventType=init");
}

void processCommand(const String& command)
{
	String key = command.substring(KEY_BEGIN, KEY_END);
	String value = command.substring(VALUE_BEGIN);

	if (key == "TP")
	{

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

	delay(3000);
}

void heartbeat()
{
	sendRequest("http://192.168.0.104:55155/api/heartbeat");
	Serial.write("HEARTBEAT\t");
}

String sendRequest(String address) 
{
	String payload = "";
	if ((WiFiMulti.run() == WL_CONNECTED)) 
	{
		HTTPClient http;

		http.begin(address);

		int httpCode = http.GET();

		// httpCode will be negative on error
		if (httpCode > 0) 
		{
			Serial.printf("[HTTP] GET... code: %d\n", httpCode);

			if (httpCode == HTTP_CODE_OK) 
			{
				payload = http.getString();
				Serial.println(payload);
			}
		}
		else
			Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());

		http.end();
	}

	return payload;
}
