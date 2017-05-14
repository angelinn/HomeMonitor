#pragma once

#include <TimeLib.h>
#include <Arduino.h>

class TimeKeeper
{
public:
	void Set(time_t);
	bool Now(String &, String &);

private:
	time_t last;
};