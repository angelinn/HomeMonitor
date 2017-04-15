#pragma once

class String;

class ESPCommunication
{
public:
	void Initialize();
	void SendMessage(const char *);
	int ReceiveMessage();
};