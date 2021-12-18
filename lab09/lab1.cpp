// 利用RTOS中3條以上thread完成跑馬燈，按下開發板上按鈕切換至下一個狀態。
// 1. 每隔１秒亮一顆LED，共８顆輪流亮。
// 2. 每隔１秒同時亮兩顆LED。
// 3. 每隔１秒亮一顆LED且每隔0.5秒亮一顆LED(同時)。
// 4. LED燈全部閃爍。

#include "mbed.h"
#include "rtos.h"
// globel variable
volatile int counter = 0;
volatile int counter_thread3 = 0;

// multi-thread
void led_thread1();
void led_thread2();
void led_thread3();
void led_thread4();

// 創建DigitalOut屬性指標陣列
DigitalOut *LED_X[8];

// 創建線程
Thread thread1;
Thread thread2;
Thread thread3;
Thread thread4;

int main() {
    // 在heap區開闢空間，創建匿名有參構造函數，初始值為0，並將其回傳的指標紀錄在指標陣列
    LED_X[0] = new DigitalOut(PC_8, 0);
    LED_X[1] = new DigitalOut(PC_9, 0);
    LED_X[2] = new DigitalOut(PC_10, 0);
    LED_X[3] = new DigitalOut(PC_11, 0);
    LED_X[4] = new DigitalOut(PC_12, 0);
    LED_X[5] = new DigitalOut(PD_2, 0);
    LED_X[6] = new DigitalOut(PG_2, 0);
    LED_X[7] = new DigitalOut(PG_3, 0);

    //resolve debouncing
    Timer timer;
    timer.start();

    // button setting
    DigitalIn button(USER_BUTTON);  // the button on your board
    if (button.is_connected()) {
        printf("----------------------\r\n");
        printf("button is connected and initialized!\r\n");
    }

    button.mode(PullNone);  // floating

    // record current state
    int state = 0;

    // activate thread
    thread1.start(callback(led_thread1));
    thread2.start(callback(led_thread2));
    thread3.start(callback(led_thread3));
    thread4.start(callback(led_thread4));

    while (true) {
        // button input and solving de-bouncing hardware problem
        int t_ms = timer.read_ms();
        if (button.read() && t_ms > 300) {
            printf("\r----------------------\r\n");
            printf("button being pressed\r\n");
            state++;

            // set all LED to OFF
            if (state % 4 == 0) {
                for (int k = 0; k < 8; k++)
                    (*LED_X[k]) = 0;
            }

            // another variable to store LED state in thread 3
            if (state % 4 == 2) {
                counter_thread3 = counter;
            }
            timer.reset();
        }

        switch (state % 4) {
            case 0:
                thread1.signal_set(0x1);
                break;
            case 1:
                thread2.signal_set(0x1);
                break;
            case 2:
                thread1.signal_set(0x1);
                thread3.signal_set(0x1);
                break;
            case 3:
                thread4.signal_set(0x1);
                break;
        }
    }

    // release all memory in heap region
    // for (int k = 0; k < 8; k++)
    //     delete LED_X[k];
}

// 每隔１秒亮一顆LED，總共８顆輪流。
void led_thread1() {
    while (true) {
        // Signal flags that are reported as event are automatically cleared.
        Thread::signal_wait(0x1);
        printf("\rthread1 executing\r\n");
        int i = counter % 8;
        (*LED_X[i]) = !(*LED_X[i]);
        printf("led_order [%d] blink\r\n", i);
        Thread::wait(1000);
        (*LED_X[i]) = !(*LED_X[i]);
        counter++;
    }
}

// 每隔１秒同時亮兩顆LED。
void led_thread2() {
    while (true) {
        // Signal flags that are reported as event are automatically cleared.
        Thread::signal_wait(0x1);
        printf("\rthread2 executing\r\n");
        int i = counter % 8;
        int j = (counter % 8 == 7) ? 0 : (i + 1);  // i is max, number 7
        (*LED_X[i]) = !(*LED_X[i]);
        (*LED_X[j]) = !(*LED_X[j]);
        printf("led_order [%d] blink\r\n", i);
        printf("led_order [%d] blink\r\n", j);
        Thread::wait(1000);
        (*LED_X[i]) = !(*LED_X[i]);
        (*LED_X[j]) = !(*LED_X[j]);
        counter++;
    }
}

// 每隔0.5秒亮一顆LED，總共８顆輪流。
void led_thread3() {
    while (true) {
        // Signal flags that are reported as event are automatically cleared.
        Thread::signal_wait(0x1);
        printf("\rthread3 executing\r\n");
        int i = counter_thread3 % 8;
        (*LED_X[i]) = !(*LED_X[i]);
        Thread::wait(500);
        (*LED_X[i]) = !(*LED_X[i]);
        counter_thread3++;
    }
}

// LED燈全部閃爍。
void led_thread4() {
    while (true) {
        Thread::signal_wait(0x1);
        printf("\rthread4 executing\r\n");
        for (int i = 0; i < 8; i++)
            (*LED_X[i]) = !(*LED_X[i]);
        Thread::wait(1000);
    }
}