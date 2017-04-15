void setup()
{
	Serial.begin(9600);

	Serial.println("Hello. I'm ESP8266. Nice to collaborate with you.");
}

String message = "";

void loop()
{
	while (Serial.available())
	{
		message = Serial.readString();
		Serial.write("OK");
		Serial.print(message);
	}
	Serial.println("End loop");
	delay(1000);
}