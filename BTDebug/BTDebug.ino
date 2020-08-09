#include <SoftwareSerial.h>

/*
	pin10 : RX connect with TXD
	pin11 : TX connect with RXD
*/
SoftwareSerial BT(10, 11);
// cache buffer
char ch;
bool status;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    status = false;

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
        if (ch == '1')
        {
            if (status)
                digitalWrite(LED_BUILTIN, HIGH);
            else
                digitalWrite(LED_BUILTIN, LOW);

            status = !status;
        }
    }
}
