#ifndef BT_H
#define BT_H

#include <SoftwareSerial.h>

/*
	pin10 : RX 连接 TXD
	pin11 : TX 连接 RXD
*/
SoftwareSerial BT(10, 11);

const byte numChars = 16;
char buffer[numChars]; // 缓存块
bool newBuffer = false;

void BTSetup();	 // 蓝牙初始化
void BTRead();	 // 读取蓝牙数据
void BTConfig(); // 蓝牙配置

#endif