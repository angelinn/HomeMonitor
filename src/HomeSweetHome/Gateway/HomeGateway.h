#pragma once

#include "ESP\ESPCommunication.h"
#include "DHT\DHTController.h"
#include "DoorSwitch\ReedSwitchController.h"
#include "RFID\RFIDController.h"

class HomeGateway
{
public:
	void Initialize();
	void ExecuteLoop();

	// Communication
private:
	ESPCommunication esp;

	// Sensors
private:
	DHTController dht;
	ReedSwitchController door;
	RFIDController rfid;

private:
	String espMessage;
	int temperature = 0;
	int humidity = 0;
};