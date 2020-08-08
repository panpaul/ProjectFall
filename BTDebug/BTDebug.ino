#include <SoftwareSerial.h>

/*
	pin10 : RX connect with TXD
	pin11 : TX connect with RXD
*/
SoftwareSerial BT(10, 11);
// cache buffer
char ch;

void setup()
{
    Serial.begin(9600);
    // HC-05
    BT.begin(9600);
}

void loop()
{
    if (Serial.available())
    {
        ch = Serial.read();
        // forward data
        BT.print(ch);
    }

    if (BT.available())
    {
        ch = BT.read();
        Serial.print(ch);
    }
}
