#include "mbed.h"
#include "LobotSerialServo.h"
// #include <cstdint>
// #include <stdarg.h>
// #include <string.h>

#define GET_LOW_BYTE(A) ((uint8_t)(A))
//宏函数 获得A的低八位
#define GET_HIGH_BYTE(A) ((uint8_t)((A) >> 8))
//宏函数 获得A的高八位
#define BYTE_TO_HW(A, B) ((((uint16_t)(A)) << 8) | (uint8_t)(B))
//宏函数 将高低八位合成为十六位

// BufferedSerial serial_port(D8, D2, 115200); // USBTX and USBRX are the default pins for the virtual serial port over USB

// uint8_t LobotRxBuf[16];
	
uint8_t LobotCheckSum(uint8_t buf[])
{
  uint8_t i;
  uint16_t temp = 0;
  for (i = 2; i < buf[3] + 2; i++) {
    temp += buf[i];
  }
  temp = ~temp;
  i = (uint8_t)temp;
  return i;
}

void LobotSerialServoSetID(BufferedSerial &SerialX, uint8_t oldID, uint8_t newID)
{
	uint8_t buf[7];
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = oldID;
  buf[3] = 4;
  buf[4] = LOBOT_SERVO_ID_WRITE;
  buf[5] = newID;
  buf[6] = LobotCheckSum(buf);
  SerialX.write(buf, 7);
}

void LobotSerialServoMove(BufferedSerial &SerialX, uint8_t id, int16_t position, uint16_t time)
{
  uint8_t buf[10];
  if(position < 0)
    position = 0;
  if(position > 1000)
	position = 1000;
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 7;
  buf[4] = LOBOT_SERVO_MOVE_TIME_WRITE;
  buf[5] = GET_LOW_BYTE(position);
  buf[6] = GET_HIGH_BYTE(position);
  buf[7] = GET_LOW_BYTE(time);
  buf[8] = GET_HIGH_BYTE(time);
  buf[9] = LobotCheckSum(buf);
  SerialX.write(buf, 10);
  printf("LobotSerialServoMove, id = %d, positon = %d, time = %d\n", id, position, time);
  printf("buf = [%x, %x, %d, %d, %d, %d, %d, %d, %d, %d]\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7], buf[8], buf[9]);
}

/*
void LobotSerialServoUnload(uint8_t id)
{
  uint8_t buf[7];
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 4;
  buf[4] = LOBOT_SERVO_LOAD_OR_UNLOAD_WRITE;
  buf[5] = 0;
  buf[6] = LobotCheckSum(buf);
  LobotSerialWrite(buf, 7);
}

void LobotSerialServoLoad(uint8_t id)
{
  uint8_t buf[7];
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 4;
  buf[4] = LOBOT_SERVO_LOAD_OR_UNLOAD_WRITE;
  buf[5] = 1;
  buf[6] = LobotCheckSum(buf);
  LobotSerialWrite(buf, 7);
}

int LobotSerialServoReadPosition(uint8_t id)
{
  int ret;
  uint8_t buf[6];

  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 3;
  buf[4] = LOBOT_SERVO_POS_READ;
  buf[5] = LobotCheckSum(buf);
	
	LobotSerialWrite(buf, 6);
	
	ret = LobotSerialMsgHandle();
  return ret;
}

int LobotSerialMsgHandle(void)
{
	int count = 50000;
	uint8_t cmd;
	int ret;
	
	while(!serial_port.readable())
	{
		count--;
		if(count < 0)
			return -2048;
	}
	
	if(LobotCheckSum(LobotRxBuf) != LobotRxBuf[LobotRxBuf[3]+2])
	{
		return -2049;
	}
	
	cmd = LobotRxBuf[4];
	switch(cmd)
	{
		case LOBOT_SERVO_POS_READ:
			ret = (int)BYTE_TO_HW(LobotRxBuf[6], LobotRxBuf[5]);
			return ret;
		default:
			break;
	}
	return 0;
}
*/
