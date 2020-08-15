#include "Sensor.h"
#include "BT.h"

//#define PRINT2SERIAL

// 输出
void Print2BT();
void Print2Serial();

// 运行状态
const byte COMMAND_START = 0;
const byte COMMAND_STOP = 1;
const byte COMMAND_RECALC = 2;
// 当前运行状态
byte currentStatus = COMMAND_STOP;

// 指令解析
void ParseBuffer();

void blink();

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(9600);

    WireSetup();
    BTSetup();

    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    CalcOffset();
    digitalWrite(LED_BUILTIN, LOW);

    Serial.println("[Setup]finished!");
}

void loop()
{
    BTRead();
    ParseBuffer();

    switch (currentStatus)
    {
    case COMMAND_START: // 正常工作
        digitalWrite(LED_BUILTIN, HIGH);
        ReadData();
        Calibrate();
        Print2BT();

#ifdef PRINT2SERIAL
        Print2Serial();
#endif

        delay(20);
        break;

    case COMMAND_STOP: // 停止工作
        digitalWrite(LED_BUILTIN, LOW);
        delay(1000);
        break;

    case COMMAND_RECALC: // 重新校准
        blink();
        digitalWrite(LED_BUILTIN, HIGH);
        CalcOffset();
        blink();
        currentStatus = COMMAND_START;
        delay(20);
        break;

    default: // 一定是出错了~
        delay(1000);
        break;
    }
}

void ParseBuffer()
{
    if (!newBuffer)
        return;

    if (strcmp(buffer, "start") == 0)
    {
        Serial.println("[Bluetooth]Received Start command");
        currentStatus = COMMAND_START;
        newBuffer = false;
        return;
    }

    if (strcmp(buffer, "stop") == 0)
    {
        Serial.println("[Bluetooth]Received Stop command");
        currentStatus = COMMAND_STOP;
        newBuffer = false;
        return;
    }

    if (strcmp(buffer, "calibrate") == 0)
    {
        Serial.println("[Bluetooth]Received Calibrate command");
        currentStatus = COMMAND_RECALC;
        newBuffer = false;
        return;
    }
}

void Print2BT()
{
    BT.print("<");

    BT.print(ACC_X), BT.print(" ");
    BT.print(ACC_Y), BT.print(" ");
    BT.print(ACC_Z), BT.print(" ");

    BT.print(GYR_X), BT.print(" ");
    BT.print(GYR_Y), BT.print(" ");
    BT.print(GYR_Z), BT.print(" ");

    BT.print(TMP_C);

    BT.print(">");
}

void Print2Serial()
{
    Serial.print(ACC_X), Serial.print(" ");
    Serial.print(ACC_Y), Serial.print(" ");
    Serial.print(ACC_Z), Serial.print(" ");

    Serial.print(GYR_X), Serial.print(" ");
    Serial.print(GYR_Y), Serial.print(" ");
    Serial.print(GYR_Z), Serial.print(" ");

    Serial.println(TMP_C);
}

void blink()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
}
