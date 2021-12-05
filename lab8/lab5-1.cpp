// 一開始LED1閃爍，使用Timeout 5秒後轉為閃爍LED2。
#include "mbed.h"
RawSerial pc(USBTX, USBRX);

bool turn_on_2 = false;
DigitalOut led[2] = {LED1, LED3};

void flip();

int main() {
    // A Timeout is used to call a function at a point in the future.
    Timeout flipper;
    flipper.attach(&flip, 5.0);  // setup flipper to call flip after 5 seconds

    while (1) {
        if (turn_on_2) {
            led[1] = !led[1];
            wait(0.2);
        } else {
            led[0] = !led[0];
            wait(0.2);
        }
    }
}

void flip() {
    pc.printf("enter ISR");
    turn_on_2 = true;
    led[0].write(0);
}