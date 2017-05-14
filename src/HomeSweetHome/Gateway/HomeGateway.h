#pragma once

#include "ESP\ESPCommunication.h"
#include "DHT\DHTController.h"
#include "DoorSwitch\ReedSwitchController.h"
#include "RFID\RFIDController.h"
#include "LCD\LCDController.h"
#include "Timing\TimeKeeper.h"

class HomeGateway
{
public:
	void Initialize();
	void ExecuteLoop();

private:
	void ProcessMessage();
	void UpdateTime();
	void UpdateTemperature();

	// Communication
private:
	ESPCommunication esp;

	// Sensors
private:
	DHTController dht;
	ReedSwitchController door;
	RFIDController rfid;
	LCDController lcd;
	TimeKeeper time;

private:
	String espMessage;
	int temperature = 0;
	int humidity = 0;
	String date;
	String currentTime;
};