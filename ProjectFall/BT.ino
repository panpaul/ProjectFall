#include "BT.h"

void BTSetup()
{
    BT.begin(9600);
}

void BTRead()
{
    Serial.print("[Bluetooth]Receiving Data:");
    while (BT.available())
    {
        ch = BT.read();
        Serial.print(ch);
    }
    Serial.println("");
}

void BTConfig()
{
    // Check whether we are in AT mode
    Serial.println("[Bluetooth]Checking whether we are in AT mode");
    BT.println("AT");
    BTRead();

    // Set bluetooth name
    Serial.println("[Bluetooth]Setting bluetooth name to \"ProjectFall\"");
    BT.println("AT+NAME=ProjectFall");
    BTRead();

    // Get bluetooth address
    Serial.println("[Bluetooth]Getting bluetooth address");
    BT.println("AT+ADDR?");
    BTRead();

    // Set bluetooth password
    Serial.println("[Bluetooth]Setting bluetooth password to \"0000\"");
    BT.println("AT+PSWD=0000");
    BTRead();
}
