#define HEARTBEAT 100
#define OK 200
#define ERROR 500


void setup()
{
	Serial.begin(9600);

	Serial.println("Hello. I'm ESP8266. Nice to collaborate with you.");
}

void processCommand(const String& command)
{
	Serial.write("OK MOTHERFUCKER\t");
}

void loop()
{
	while (Serial.available())
		processCommand(Serial.readString());

	Serial.write("HEARTBEAT\t");
	delay(1000);
}

	