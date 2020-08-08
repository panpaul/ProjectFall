#include <SoftwareSerial.h>

void BTRead();
void BTSetup();
void Blink(unsigned short times);

/*
	pin10 : RX connect with TXD
	pin11 : TX connect with RXD
*/
SoftwareSerial BT(10, 11);
// cache buffer
char ch;

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(9600);
	// HC-05
	BT.begin(38400);
}

void loop()
{
	// Blink to inform
	Blink(5);

	Serial.println("===== Begin to setup bluetooth device =====");

	// Setup bluetooth device
	digitalWrite(LED_BUILTIN, HIGH);
	BTSetup();
	digitalWrite(LED_BUILTIN, LOW);

	Serial.println("===== Finished! =====");

	delay(2000);
}

void BTSetup()
{
	// Check whether we are in AT mode
	Serial.println("> Checking whether we are in AT mode");
	BT.println("AT");
	BTRead();

	// Set bluetooth name
	Serial.println("> Setting bluetooth name to \"ProjectFall\"");
	BT.println("AT+NAME=ProjectFall");
	BTRead();

	// Get bluetooth address
	Serial.println("> Getting bluetooth address");
	BT.println("AT+ADDR?");
	BTRead();

	// Set bluetooth password
	Serial.println("> Setting bluetooth password to \"0000\"");
	BT.println("AT+PSWD=0000");
	BTRead();
}

void BTRead()
{
	delay(1000);
	Serial.print("< Received Data:");
	while (BT.available())
	{
		ch = BT.read();
		Serial.print(ch);
	}
	Serial.println("");
	delay(1000);
}

void Blink(unsigned short times)
{
	while (times--)
	{
		digitalWrite(LED_BUILTIN, HIGH);
		delay(200);
		digitalWrite(LED_BUILTIN, LOW);
		delay(200);
	}
	delay(500);
}
