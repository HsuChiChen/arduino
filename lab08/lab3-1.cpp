// 在serial monitor上輸入指令控制LED。
#include "mbed.h"
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
RawSerial pc(USBTX, USBRX, 9600);  // tx, rx

int main() {
    pc.printf("Input: 'G' LED ON; 'B' LED2 ON; 'R' LED3 ON; '1' ALL LED ON\n\r");
    while (1) {
        char cmd = pc.getc();
        pc.putc(cmd);  // echo input back to terminal
        pc.printf("\n\r");

        switch (cmd) {
            case 'G':
                led1 = !led1;
                break;
            case 'B':
                led2 = !led2;
                break;
            case 'R':
                led3 = !led3;
                break;
            case '1':
                led1 = !led1;
                led2 = !led2;
                led3 = !led3;
                break;
            default:
                pc.printf("Invalid input\n\r");
                break;
        }
    }
}