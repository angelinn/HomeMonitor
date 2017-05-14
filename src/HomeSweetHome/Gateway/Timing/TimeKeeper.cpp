#include "TimeKeeper.h"

void TimeKeeper::Set(time_t t)
{
	last = 0;
	setTime(t);
}

bool TimeKeeper::Now(String& date, String& time)
{
	Serial.println(last - now());

	char buffer[17];
	sprintf(buffer, "%d %s %d", day(), monthShortStr(month()), year());
	date = buffer;

	sprintf(buffer, "%d:%d", hour(), minute());
	time = buffer;

	return now();
}
