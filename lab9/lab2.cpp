// 利用RTOS中的signals。在serial monitor輸入指令控制開發板的LED。
// 輸入'1'亮綠燈、輸入'2'亮藍燈、輸入'3'亮紅燈。
#include "mbed.h"
#include "rtos.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

Thread thread1, thread2, thread3;
Serial pc(SERIAL_TX, SERIAL_RX);
void led1_thread();
void led2_thread();
void led3_thread();

int main(void) {
    thread1.start(callback(led1_thread));
    thread2.start(callback(led2_thread));
    thread3.start(callback(led3_thread));
    char cmd;
    pc.printf("Enter command \"1\",\"2\",\"3\"\r\n");
    while (true) {
        if (pc.readable()) {
            cmd = pc.getc();
            pc.putc(cmd);
            pc.printf("\r\n");

            switch (cmd) {
                case '1':
                    thread1.signal_set(0x1);
                    break;
                case '2':
                    thread2.signal_set(0x1);
                    break;
                case '3':
                    thread3.signal_set(0x1);
                    break;
                default:
                    led1 = 1;
                    led2 = 1;
                    led3 = 1;
                    break;
            }
        }
    }
}


void led1_thread() {
    while (true) {
        // Signal flags that are reported as event are automatically cleared.
        Thread::signal_wait(0x1);
        pc.printf("thread 1 - green LED\r\n");
        led1 = 1;
        led2 = 0;
        led3 = 0;
    }
}
void led2_thread() {
    while (true) {
        Thread::signal_wait(0x1);
        pc.printf("thread 2 - blue LED\r\n");
        led1 = 0;
        led2 = 1;
        led3 = 0;
    }
}
void led3_thread() {
    while (true) {
        Thread::signal_wait(0x1);
        pc.printf("thread 3 - red LED\r\n");
        led1 = 0;
        led2 = 0;
        led3 = 1;
    }
}