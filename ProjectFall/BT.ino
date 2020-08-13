#include "BT.h"

void BTSetup()
{
    BT.begin(9600);
}

void BTRead()
{
    /*
        数据格式 "<" + "command" + ">"
    */
    static bool receving = false;
    static byte idx = 0;
    char ch;

    while (BT.available() && newBuffer == false)
    {
        ch = BT.read();

        if (receving)
        {
            if (ch != '>')
            {
                buffer[idx] = ch;
                idx++;
                if (idx >= numChars)
                {
                    idx = numChars - 1;
                }
            }
            else
            {
                buffer[idx] = '\0';
                receving = false;
                idx = 0;
                newBuffer = true;
            }
        }
        else if (ch == '<')
        {
            receving = true;
        }
    }
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
