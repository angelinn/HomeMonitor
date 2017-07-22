#pragma once

#include "ConnectionProvider.h"

class HttpConnection : public ConnectionProvider
{
public:
	HttpConnection(ESP8266WiFiMulti* handle) : ConnectionProvider(handle)
	{   }
public:
	virtual void heartbeat();
	virtual void sendDoorData(const String &);
	virtual void sendMoveData();
	virtual void sendWeatherData(const String* params);
	virtual String requestTime();

private:
	String sendRequest(String);
	String buildUrl(String, const String* = nullptr);
};
