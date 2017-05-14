#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>

#include <ESP8266HTTPClient.h>

#define KEY_BEGIN 0
#define KEY_END 2
#define VALUE_BEGIN 3
#define DELIMITER '\t'
#define HEARTBEAT_INTERVAL 30000

unsigned int localPort = 2390;      // local port to listen for UDP packets
IPAddress timeServerIP;
const char* ntpServerName = "time.nist.gov";

const int NTP_PACKET_SIZE = 48;

byte packetBuffer[NTP_PACKET_SIZE];
WiFiUDP udp;

ESP8266WiFiMulti WiFiMulti;

unsigned long lastHeartbeat = millis();

void setup()
{
	Serial.begin(9600);
	
	WiFi.begin("The Pepper", "9582757280");
	Serial.println("Connecting to The Pepper");
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());

	Serial.println("Starting UDP");
	udp.begin(localPort);
	Serial.print("Local port: ");
	Serial.println(udp.localPort());

	WiFi.hostByName(ntpServerName, timeServerIP);

	Serial.println(timeServerIP);
	sendNTPpacket(timeServerIP);
	delay(1000);

	int cb = udp.parsePacket();
	if (!cb) {
		delay(1);
	}
	else {
		// We've received a packet, read the data from it
		udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

												 //the timestamp starts at byte 40 of the received packet and is four bytes,
												 // or two words, long. First, esxtract the two words:

		unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
		unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
		// combine the four bytes (two words) into a long integer
		// this is NTP time (seconds since Jan 1 1900):
		unsigned long secsSince1900 = highWord << 16 | lowWord;
		// Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
		const unsigned long seventyYears = 2208988800UL;
		// subtract seventy years:
		unsigned long epoch = secsSince1900 - seventyYears;
		// print Unix time:
		char buffer[128];
		Serial.flush();
		sprintf(buffer, "DT:%d\t", epoch);
		Serial.println(buffer);
	}
	
	WiFi.disconnect();

	WiFiMulti.addAP("The Pepper", "9582757280");

	sendRequest("http://192.168.0.104:55155/api/events?eventType=init");
}

void processCommand(const String& command)
{
	String key = command.substring(KEY_BEGIN, KEY_END);
	String value = command.substring(VALUE_BEGIN);

	if (key == "TP")
	{

	}
}

void loop()
{
	while (Serial.available())
		processCommand(Serial.readStringUntil(DELIMITER));

	if (millis() - lastHeartbeat > HEARTBEAT_INTERVAL)
	{
		heartbeat();
		lastHeartbeat = millis();
	}

	delay(3000);
}

void heartbeat()
{
	sendRequest("http://192.168.0.104:55155/api/heartbeat");
	Serial.write("HEARTBEAT\t");
}

void sendRequest(String address) 
{
	if ((WiFiMulti.run() == WL_CONNECTED)) 
	{
		HTTPClient http;

		http.begin(address);

		int httpCode = http.GET();

		// httpCode will be negative on error
		if (httpCode > 0) 
		{
			Serial.printf("[HTTP] GET... code: %d\n", httpCode);

			if (httpCode == HTTP_CODE_OK) 
			{
				String payload = http.getString();
				Serial.println(payload);
			}
		}
		else
			Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());

		http.end();
	}
}


unsigned long sendNTPpacket(IPAddress& address)
{
	Serial.println("sending NTP packet...");
	memset(packetBuffer, 0, NTP_PACKET_SIZE);
	packetBuffer[0] = 0b11100011;   // LI, Version, Mode
	packetBuffer[1] = 0;     // Stratum, or type of clock
	packetBuffer[2] = 6;     // Polling Interval
	packetBuffer[3] = 0xEC;  // Peer Clock Precision
	packetBuffer[12] = 49;
	packetBuffer[13] = 0x4E;
	packetBuffer[14] = 49;
	packetBuffer[15] = 52;
	udp.beginPacket(address, 123);
	udp.write(packetBuffer, NTP_PACKET_SIZE);
	udp.endPacket();
}
