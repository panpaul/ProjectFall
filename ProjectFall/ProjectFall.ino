#include "Sensor.h"
#include "BT.h"

void Print2BT();     // 蓝牙输出
void Print2Serial(); // 串口输出

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    Serial.begin(9600);

    WireSetup(); // 传感器初始化
    BTSetup();   // 蓝牙初始化

    delay(1000);
    CalcOffset(); // 计算GYR的偏移量

    Serial.println("[Setup]finished!");
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop()
{
    ReadData();  // 读取原始数据
    Calibrate(); // 校准
    Print2BT();  // 输出到蓝牙

    //Print2Serial(); // 输出到串口

    delay(20);
}

void Print2BT()
{
    BT.print(ACC_X), BT.print(" ");
    BT.print(ACC_Y), BT.print(" ");
    BT.print(ACC_Z), BT.print(" ");

    BT.print(GYR_X), BT.print(" ");
    BT.print(GYR_Y), BT.print(" ");
    BT.print(GYR_Z), BT.print(" ");

    BT.println(TMP_C);
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
