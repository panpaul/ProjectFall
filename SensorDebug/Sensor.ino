#include "Sensor.h"

void WireSetup()
{
    Wire.begin();
    Wire.beginTransmission(MPU);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);

    OFF_TIMES = 100;
    OFF_DROP = 20;
    OFF_DELAY = 10;

    ACC_X_OFF = ACC_Y_OFF = ACC_Z_OFF = GYR_X_OFF = GYR_Y_OFF = GYR_Z_OFF = 0;
}

void ReadData()
{
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.requestFrom(MPU, 14, true);
    Wire.endTransmission(true);

    // 1条数据2字节 一次读取一个字节
    ACC_X_R = (Wire.read() << 8 | Wire.read());
    ACC_Y_R = (Wire.read() << 8 | Wire.read());
    ACC_Z_R = (Wire.read() << 8 | Wire.read());
    TMP_R = (Wire.read() << 8 | Wire.read());
    GYR_X_R = (Wire.read() << 8 | Wire.read());
    GYR_Y_R = (Wire.read() << 8 | Wire.read());
    GYR_Z_R = (Wire.read() << 8 | Wire.read());
}

void Calibrate()
{
    // 温度
    // pdf: 4.18 Registers 65 and 66 – Temperature Measurement
    TMP_C = TMP_R / 340.0f + 36.53;

    // 加速度
    // pdf: 4.17 Registers 59 to 64 – Accelerometer Measurements
    ACC_X = (float)(ACC_X_R + ACC_X_OFF) / 16384.0f;
    ACC_Y = (float)(ACC_Y_R + ACC_Y_OFF) / 16384.0f;
    ACC_Z = (float)(ACC_Z_R + ACC_Z_OFF) / 16384.0f;

    // 角速度
    // pdf: 4.19 Registers 67 to 72 – Gyroscope Measurements
    GYR_X = (float)(GYR_X_R + GYR_X_OFF) / 131.0f;
    GYR_Y = (float)(GYR_Y_R + GYR_Y_OFF) / 131.0f;
    GYR_Z = (float)(GYR_Z_R + GYR_Z_OFF) / 131.0f;
}

void CalcOffset()
{
    // 角速度偏移量计算
    int x = 0, y = 0, z = 0;

    for (int16_t i = 0; i < OFF_DROP; i++)
    { // 丢弃最开始的数据
        ReadData();
        delay(100);
    }

    for (int16_t i = 0; i < OFF_TIMES; i++)
    {
        ReadData();
        x += GYR_X_R;
        y += GYR_Y_R;
        z += GYR_Z_R;
        delay(OFF_DELAY);
    }
    GYR_X_OFF = -(x / OFF_TIMES);
    GYR_Y_OFF = -(y / OFF_TIMES);
    GYR_Z_OFF = -(z / OFF_TIMES);
}
