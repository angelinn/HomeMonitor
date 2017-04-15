#pragma once

class ESPCommunication
{
public:
	void Initialize();
	void SendMessage(const char *);
	void ReceiveMessage(String &);
};