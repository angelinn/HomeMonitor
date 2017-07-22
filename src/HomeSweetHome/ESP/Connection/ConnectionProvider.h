#pragma once

class ESP8266WiFiMulti;
class String;

class ConnectionProvider
{
public:
	ConnectionProvider(ESP8266WiFiMulti* handle) : wifiHandle(handle)
	{   }
public:
	virtual void heartbeat() = 0;
	virtual void sendDoorData(const String &) = 0;
	virtual void sendMoveData() = 0;
	virtual void sendWeatherData(const String* params) = 0;
	virtual String requestTime() = 0;

protected:
	ESP8266WiFiMulti* wifiHandle;
};
