#include "TimeKeeper.h"

void TimeKeeper::Set(time_t t)
{
	last = 0;
	setTime(t);
}

bool TimeKeeper::Now(String& date, String& time)
{
	if (now() - last > 60)
	{
		Serial.println(now() - last);

		char buffer[17];
		sprintf(buffer, "%d %s %d", day(), monthShortStr(month()), year());
		date = buffer;

		char* hourPrefix = "";
		char* minutePrefix = "";

		if (hour() < 10)
			hourPrefix = "0";
		if (minute() < 10)
			minutePrefix = "0";

		sprintf(buffer, "%s%d:%s%d", hourPrefix, hour(), minutePrefix, minute());
		time = buffer;

		last = now();
		return now();
	}
	return false;
}

