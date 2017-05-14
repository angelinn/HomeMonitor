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
#define PASSWORD "95827572580"

#define API_URL "http://192.168.0.103:55155/api"
#define HEARTBEAT_URL API_URL "" "/device/heartbeat?id=1"
#define TIME_URL API_URL "" "/time"

ESP8266WiFiMulti WiFiMulti;

unsigned long lastHeartbeat = millis();

String buildUrl(String action, const String* params = nullptr)
{
	char buffer[128];
	if (action == "move")
		sprintf(buffer, "%s/movement", API_URL);
	else if (action == "weather")
		sprintf(buffer, "%s/weather?temperature=%d&humidity=%d", API_URL, params[0].c_str(), params[1].c_str());
	else if (action == "door")
		sprintf(buffer, "%s/door?status=%d", params[0].c_str());

	Serial.printf("Build %s\n", buffer);
	return buffer;
}

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

	String time = sendRequest(TIME_URL);
	char buffer[32];
	sprintf(buffer, "DT:%s\t", time.c_str());
	Serial.print(buffer);

	heartbeat();
}

void processCommand(const String& command)
{
	String key = command.substring(KEY_BEGIN, KEY_END);
	String value = command.substring(VALUE_BEGIN);

	Serial.printf("GOT %s\n", key.c_str());
	Serial.printf("GOT VALUE %s\n", value.c_str());
	if (key == "TP")
	{
		String params[] = { value.substring(0, 2), value.substring(2, 4) };
		sendRequest(buildUrl("weather, params"));
	}
	else if (key == "RS")
	{
		String params[] = { value };
		String res = sendRequest(buildUrl("door", params));
		Serial.printf("RS:%s\t", res.c_str());
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
	sendRequest(HEARTBEAT_URL);
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
			Serial.printf("[HTTP] GET %s ... code: %d\n", address.c_str(), httpCode);

			if (httpCode == HTTP_CODE_OK)
			{
				payload = http.getString();
				Serial.println(payload);
			}
		}
		else
			Serial.printf("[HTTP] GET %s ... failed, error: %s\n", address.c_str(), http.errorToString(httpCode).c_str());

		http.end();
	}

	return payload;
}

