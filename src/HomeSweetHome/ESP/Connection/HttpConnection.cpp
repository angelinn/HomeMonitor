#include "HttpConnection.h"
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#define API_URL "http://192.168.0.103:55155/api"
#define HEARTBEAT_URL API_URL "" "/device/heartbeat?id=1"
#define TIME_URL API_URL "" "/time"

void HttpConnection::heartbeat()
{
	sendRequest(HEARTBEAT_URL);
}

String HttpConnection::requestTime()
{
	return sendRequest(TIME_URL);
}

void HttpConnection::sendDoorData(const String& status)
{
	sendRequest(buildUrl("door", &status));
}

void HttpConnection::sendMoveData()
{
	sendRequest(buildUrl("move"));
}

void HttpConnection::sendWeatherData(const String* params)
{
	sendRequest(buildUrl("weather", params));
}

String HttpConnection::sendRequest(String address)
{
	String payload = "";
	if ((wifiHandle->run() == WL_CONNECTED))
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

String HttpConnection::buildUrl(String action, const String* params)
{
	char buffer[256];
	if (action == "move")
		sprintf(buffer, "%s/events/movement", API_URL);
	else if (action == "weather")
		sprintf(buffer, "%s/events/weather?temperature=%s&humidity=%s", API_URL, params[0].c_str(), params[1].c_str());
	else if (action == "door")
		sprintf(buffer, "%s/events/door?status=%s", API_URL, params[0].c_str());

	Serial.printf("Build %s\n", buffer);
	return buffer;
}
