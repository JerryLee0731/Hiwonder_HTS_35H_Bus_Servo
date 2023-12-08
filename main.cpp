#include "mbed.h"

#include "LobotSerialServo.h"

#define ID1 1

 int main(void)
 {	
    BufferedSerial serial_port(D8, D2, 115200);
    ThisThread::sleep_for(1000ms);
    #ifdef LED1
        DigitalOut led(LED1);
    #else
        bool led;
    #endif

	while(1)
	{
        printf("\nloop\n"); 
        LobotSerialServoMove(serial_port, ID1, 100, 1000);  //舵机1用500ms转动到100位置
        led = !led;
        ThisThread::sleep_for(2000ms);
        LobotSerialServoMove(serial_port, ID1, 500, 1000);  //舵机1用500ms转动到500位置
        led = !led;
        ThisThread::sleep_for(2000ms);
        /*
        LobotSerialServoMove(serial_port, ID1, 900, 800);  //舵机1用800ms转动到900位置
        led = !led;
        ThisThread::sleep_for(1000ms);
        LobotSerialServoMove(serial_port, ID1, 500, 800);  //舵机1用800ms转动到700位置
        led = !led;
        ThisThread::sleep_for(1000ms);
        */
	}
}