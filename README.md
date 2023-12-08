# Hiwonder_HTS_35H_Bus_Servo
## 使用方式
1. 將LobotSerialServo.h LobotSerialServo.cpp加入project資料夾
2. 在你的主程式中#include "LobotSerialServo.h"
## 主要函式
1. void LobotSerialServoMove(BufferedSerial &SerialX, uint8_t id, int16_t position, uint16_t time);
   - BufferedSerial &SerialX 傳入一個BufferedSerail物件，baudrate要設為115200
   - id為servo id
   - position為欲轉動到的角度
   - time為多久轉到該角度
2. void LobotSerialServoSetID(BufferedSerial &SerialX, uint8_t oldID, uint8_t newID);
   - id預設為0，故若有多個servo，要先設定新id，避免id衝突
## 硬體
伺服馬達接頭，由左中右分別為GND、VIN、SIG。
- VIN為11.1V
- SIG接到stm32上BufferSerial設定的tx腳位
