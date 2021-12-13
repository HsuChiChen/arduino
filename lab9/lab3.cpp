// 利用RTOS中的signals。將超音波模組測量到的距離(cm)顯示2位於七段顯示器，並控制開發板的LED為

// |距離(cm)|LED|
// |:-:|:-:|
// |$d < 10$|紅燈|
// |$d \in [10,15]$|藍燈|
// |$d \in [15,20]$|綠燈|
// |$$d > 20$$|全亮|

#include "mbed.h"
#include "rtos.h"
#include "ultrasonic.h"

// decalartion of function
void show_digit();
void number_transfer(int);
void SEG_Drive(int);

void led1_thread();
void led2_thread();
void led3_thread();
void led_all_thread();

void dist(int);

// variable for 7-seg
DigitalOut *SEG_COM[4];         //control signal
DigitalOut *digit[8];           //each digit
const int SEG_data[10][8] = {   //data line
    {1, 1, 1, 1, 1, 1, 0, 0},   //"0"
    {0, 1, 1, 0, 0, 0, 0, 0},   //"1"
    {1, 1, 0, 1, 1, 0, 1, 0},   //"2"
    {1, 1, 1, 1, 0, 0, 1, 0},   //"3"
    {0, 1, 1, 0, 0, 1, 1, 0},   //"4"
    {1, 0, 1, 1, 0, 1, 1, 0},   //"5"
    {1, 0, 1, 1, 1, 1, 1, 0},   //"6"
    {1, 1, 1, 0, 0, 0, 0, 0},   //"7"
    {1, 1, 1, 1, 1, 1, 1, 0},   //"8"
    {1, 1, 1, 0, 0, 1, 1, 0}};  //"9"
int disp[4];                    //number to display

// variable for ultrasonic
DigitalOut trigger(D0);
DigitalOut echo(D1);
ultrasonic mu(D0, D1, .1, 1, &dist);
int cm = 0;

// variable for LED
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

// thread
Thread thread1, thread2, thread3, thread_all;

int main() {
    // 7-seg
    SEG_COM[0] = new DigitalOut(D10);
    SEG_COM[1] = new DigitalOut(D11);

    digit[0] = new DigitalOut(D2);
    digit[1] = new DigitalOut(D3);
    digit[2] = new DigitalOut(D4);
    digit[3] = new DigitalOut(D5);
    digit[4] = new DigitalOut(D6);
    digit[5] = new DigitalOut(D7);
    digit[6] = new DigitalOut(D8);
    digit[7] = new DigitalOut(D9);  // dp

    // thread
    thread1.start(callback(led1_thread));
    thread2.start(callback(led2_thread));
    thread3.start(callback(led3_thread));
    thread_all.start(callback(led_all_thread));

    //start mesuring the distance
    mu.startUpdates();

    while (true) {
        mu.checkDistance();
        if (cm < 10) {  //led3  red
            thread3.signal_set(0x1);
        } else if (cm > 10 && cm < 15) {  //led2  blue
            thread2.signal_set(0x1);
        } else if (cm > 15 && cm < 20) {  //led1  green
            thread1.signal_set(0x1);
        } else {  //all
            thread_all.signal_set(0x1);
        }
        show_digit();
    }
}

void led1_thread() {
    while (true) {
        Thread::signal_wait(0x1);
        led1 = 1;
        led2 = 0;
        led3 = 0;
    }
}
void led2_thread() {
    while (true) {
        Thread::signal_wait(0x1);
        led1 = 0;
        led2 = 1;
        led3 = 0;
    }
}
void led3_thread() {
    while (true) {
        Thread::signal_wait(0x1);
        led1 = 0;
        led2 = 0;
        led3 = 1;
    }
}
void led_all_thread() {
    while (true) {
        Thread::signal_wait(0x1);
        led1 = 1;
        led2 = 1;
        led3 = 1;
    }
}

void show_digit() {
    number_transfer(cm);
    int init = (cm <= 9) ? 1 : 2;
    for (int i = 0; i < init; i++) {
        (*SEG_COM[i]).write(0);
        SEG_Drive(disp[i]);
        wait(0.005);
        (*SEG_COM[i]).write(1);

        //show point at second digit
        if (i == 1)
            (*digit[7]).write(1);
        else
            (*digit[7]).write(0);
    }
}

//三位數拆成三個獨立的數字，存入陣列disp[]中
void number_transfer(int num) {
    for (int i = 0; i < 4; i++) {
        disp[i] = num % 10;  //取餘數
        num = num / 10;
    }
}

//將字元變數從SEG_data[][]找到相對應的位置，並寫入a~g中
void SEG_Drive(int number) {
    for (int i = 0; i < 7; i++)
        (*digit[i]).write(SEG_data[number][i]);
}

void dist(int distance) {
    cm = distance / 10;
    printf("Distance %d cm\r\n", cm);
}