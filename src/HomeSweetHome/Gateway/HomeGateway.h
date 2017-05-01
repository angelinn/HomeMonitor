#pragma once

#include "ESP\ESPCommunication.h"
#include "DHT\DHTController.h"
#include "DoorSwitch\ReedSwitchController.h"
#include "RFID\RFIDController.h"
#include "LCD\LCDController.h"

class HomeGateway
{
public:
	void Initialize();
	void ExecuteLoop();

private:
	void ProcessMessage();

	// Communication
private:
	ESPCommunication esp;

	// Sensors
private:
	DHTController dht;
	ReedSwitchController door;
	RFIDController rfid;
	LCDController lcd;

private:
	String espMessage;
	int temperature = 0;
	int humidity = 0;
};