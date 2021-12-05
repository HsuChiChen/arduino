// 以LED1~3實現單向跑馬燈。
#include "mbed.h"

int main() {
    //創建DigitalOut屬性指標陣列
    DigitalOut *LED_X[3];
    //在heap區開闢空間，創建匿名有參構造函數，並將其回傳的指標紀錄在指標陣列
    LED_X[0] = new DigitalOut(LED1);
    LED_X[1] = new DigitalOut(LED2);
    LED_X[2] = new DigitalOut(LED3);
    int i = 0;
    // Blink LED
    while (1) {
        (*LED_X[i%3]) = !(*LED_X[i%3]);
        wait(1);
        (*LED_X[i%3]) = !(*LED_X[i%3]);
        i++;
    }
    // //release memory in heap region
    // for (int k = 0; k < 3; k++)
    //     delete LED_X[k];
}