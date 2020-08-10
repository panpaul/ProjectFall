#ifndef SENSOR_H
#define SENSOR_H

#include <Wire.h>

const int MPU = 0x68; // MPU-6050的I2C地址

int16_t ACC_X_R, ACC_Y_R, ACC_Z_R, TMP_R, GYR_X_R, GYR_Y_R, GYR_Z_R; // 获取到的原始数据: 加速度+温度+角速度

int16_t OFF_TIMES, OFF_DELAY, OFF_DROP;                                   // 偏移量取值个数+周期+丢弃数量
int16_t ACC_X_OFF, ACC_Y_OFF, ACC_Z_OFF, GYR_X_OFF, GYR_Y_OFF, GYR_Z_OFF; // 校准用偏移量

float ACC_X, ACC_Y, ACC_Z, TMP_C, GYR_X, GYR_Y, GYR_Z; // 校准后的数据

void WireSetup();  // 传感器初始化
void ReadData();   // 读取原始数据
void Calibrate();  // 校准
void CalcOffset(); // 计算偏移量

#endif