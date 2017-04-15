#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

#define HEARTBEAT 100
#define OK 200
#define ERROR 500

ESP8266WiFiMulti WiFiMulti;

void setup()
{
	Serial.begin(9600);
	Serial.println();
	Serial.println();
	Serial.println();

	for (uint8_t t = 4; t > 0; t--) {
		Serial.printf("[SETUP] WAIT %d...\n", t);
		Serial.flush();
		delay(1000);
	}

	WiFiMulti.addAP("The Pepper", "9582757280");


	sendRequest("http://192.168.0.104:55155/api/init");
	Serial.println("Hello. I'm ESP8266. Nice to collaborate with you.\t");
}

void processCommand(const String& command)
{
	Serial.write("OK MOTHERFUCKER\t");
}

void loop()
{
	while (Serial.available())
		processCommand(Serial.readStringUntil('\t'));

	heartbeat();
	delay(1000);
}

void heartbeat()
{
	sendRequest("http://192.168.0.104:55155/api/heartbeat");
	Serial.write("HEARTBEAT\t");
}

void sendRequest(String address) {
	// wait for WiFi connection
	if ((WiFiMulti.run() == WL_CONNECTED)) 
	{
		HTTPClient http;

		Serial.print("[HTTP] begin...\n");
		// configure traged server and url
		//http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
		http.begin(address); //HTTP

		Serial.print("[HTTP] GET...\n");
		// start connection and send HTTP header
		int httpCode = http.GET();

		// httpCode will be negative on error
		if (httpCode > 0) {
			// HTTP header has been send and Server response header has been handled
			Serial.printf("[HTTP] GET... code: %d\n", httpCode);

			// file found at server
			if (httpCode == HTTP_CODE_OK) {
				String payload = http.getString();
				Serial.println(payload);
			}
		}
		else {
			Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
		}

		http.end();
	}
}

	