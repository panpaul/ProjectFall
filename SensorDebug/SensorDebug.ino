#include "Sensor.h"

void Print(); // 串口输出

void setup()
{
    Serial.begin(9600);

    WireSetup(); // 传感器初始化

    delay(1000);
    CalcOffset(); // 计算GYR的偏移量
}

void loop()
{
    ReadData();  // 读取原始数据
    Calibrate(); // 校准
    Print();     // 打印到串口
    delay(20);
}

void Print()
{
    Serial.println("========================================");

    Serial.print("ACC_X: "), Serial.print(ACC_X);
    Serial.print(" ACC_Y: "), Serial.print(ACC_Y);
    Serial.print(" ACC_Z: "), Serial.println(ACC_Z);

    Serial.print("GYR_X: "), Serial.print(GYR_X);
    Serial.print(" GYR_Y: "), Serial.print(GYR_Y);
    Serial.print(" GYR_Z: "), Serial.println(GYR_Z);

    Serial.print("TEMP: "), Serial.println(TMP_C);

    Serial.println("========================================");
}
