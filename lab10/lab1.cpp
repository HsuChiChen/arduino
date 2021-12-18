// 利用RTOS中的`Thread`, `Semaphore`, `Mutex`完成跑馬燈，按下開發板上的按鈕切換至下一個狀態。
// 1. 每隔１秒亮1顆LED，共3顆輪流亮。
// 2. 每隔１秒同時亮2顆LED。(`Semaphore`狀態)
// 3. 每隔１秒LED燈全部閃爍。(`Mutex`狀態)

#include "mbed.h"
#include "rtos.h"
// globel variable
volatile int counter = 0;
volatile int counter_thread2 = 0;

// multi-thread
// state 1
void led_thread1();
// state 2 - 允許2個thread的semaphore
Semaphore two_slots(2);
void semaphore_fun(DigitalOut *led);
// state 3 - (允許1個thread的)mutex
Mutex stdio_mutex;
void mutex_fun(DigitalOut *led);
bool IsPressed = true;
// 創建線程
Thread thread1;
Thread thread2;
Thread thread3;
Thread thread4;
Thread thread5;
Thread thread6;
Thread thread7;
Thread thread8;

// 新增LED對象
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

// the button on your board
DigitalIn button(USER_BUTTON);

// record current state
int state = 0;
Timer timer;

int main() {
    //resolve debouncing
    timer.start();

    // button setting
    if (button.is_connected()) {
        printf("----------------------\r\n");
        printf("button is connected and initialized!\r\n");
    }

    button.mode(PullNone);  // floating

    // activate thread
    thread1.start(callback(led_thread1));

    while (true) {
        // button input and solving de-bouncing hardware problem
        //int t_ms = timer.read_ms();

        if (IsPressed) {
            IsPressed = false;
            switch (state % 3) {
                case 0:
                    thread1.signal_set(0x1);
                    break;
                case 1:
                    thread2.start(callback(semaphore_fun, &led2));  // same resource
                    thread3.start(callback(semaphore_fun, &led2));  // same resource
                    thread4.start(callback(semaphore_fun, &led3));  // same resource
                    thread5.start(callback(semaphore_fun, &led3));  // same resource
                    thread6.start(callback(semaphore_fun, &led1));  // same resource
                    semaphore_fun(&led1);
                    break;
                case 2:
                    thread7.start(callback(mutex_fun, &led1));  // same resource
                    thread8.start(callback(mutex_fun, &led2));  // same resource
                    mutex_fun(&led3);
                    break;
            }
        }
    }

    // release all memory in heap region
    // for (int k = 0; k < 3; k++)
    //     delete LED_X[k];
}

// 每隔１秒亮一顆LED，總共3顆輪流。
void led_thread1() {
    while (state % 3 == 0) {
        // Signal flags that are reported as event are automatically cleared.
        Thread::signal_wait(0x1);
        printf("\rthread1 executing\r\n");
        int i = counter % 3;
        printf("led_order [%d] blink\r\n", i);
        switch (i) {
            case 0:
                led1 = 1;
                led2 = 0;
                led3 = 0;
                break;
            case 1:
                led1 = 0;
                led2 = 1;
                led3 = 0;
                break;
            case 2:
                led1 = 0;
                led2 = 0;
                led3 = 1;
                break;
        }
        Thread::wait(1000);
        led1 = 0;
        led2 = 0;
        led3 = 0;
        counter++;

        if (button.read()) {
            IsPressed = true;
            printf("\r----------------------\r\n");
            printf("button being pressed\r\n");
            // all LED turn off
            led1 = 0;
            led2 = 0;
            led3 = 0;
            state = 1;
            timer.reset();
        }
    }
}

// 6 thread share one resource (semaphore)
void semaphore_fun(DigitalOut *led) {
    while (state % 3 == 1) {
        two_slots.wait();
        *led = !*led;
        printf("%p\r\n", *led);
        Thread::wait(1000);
        *led = !*led;
        two_slots.release();
        int t_ms = timer.read_ms();
        if (button.read() && t_ms > 500) {
            printf("\r----------------------\r\n");
            printf("button being pressed\r\n");
            // all LED turn off
            IsPressed = true;
            led1 = 0;
            led2 = 0;
            led3 = 0;
            state = 2;
            timer.reset();
            two_slots.release();
        }
    }
    printf("-----break test1-------");
}

// 3 thread share one resource (mutex)
void mutex_fun(DigitalOut *led) {
    while (state % 3 == 2) {
        stdio_mutex.lock();
        printf("%p\r\n", *led);
        *led = !*led;
        stdio_mutex.unlock();
        Thread::wait(1000);
        int t_ms = timer.read_ms();
        if (button.read() && t_ms > 500) {
            state = 0;
            IsPressed = true;
            break;
        }
    }
    printf("\r----------------------\r\n");
    printf("button being pressed\r\n");
    // all LED turn off
    led1 = 0;
    led2 = 0;
    led3 = 0;

    timer.reset();
    printf("-----break test2-------");
}