#pragma once

class String;

class ReedSwitchController 
{
public:
	void Initialize();
	bool IsDoorClosed(String& message);
};
