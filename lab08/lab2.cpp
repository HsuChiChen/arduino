// 承lab1，在USER_BUTTON被按下時停止，放開時LED跑馬燈會往反方向。
#include "mbed.h"

int main() {
    // button setting
    DigitalIn button(USER_BUTTON);  // the button on your board
    if (button.is_connected())
        printf("button is connected and initialized! \n\r");
    button.mode(PullNone);  // floating

    // 創建DigitalOut屬性指標陣列
    DigitalOut *LED_X[3];
    // 在heap區開闢空間，創建匿名有參構造函數，並將其回傳的指標紀錄在指標陣列
    LED_X[0] = new DigitalOut(LED1);
    LED_X[1] = new DigitalOut(LED2);
    LED_X[2] = new DigitalOut(LED3);
    int i = 5000;
    // direction
    bool clockwise = true;

    // Blink LED
    while (1) {
        // LED ON
        (*LED_X[i % 3]) = !(*LED_X[i % 3]);
        wait(0.3);

        // button being pressed
        if (button.read()) {
            clockwise = !clockwise;
            while (1) {
                if (!button.read()) // button being released
                    break;
            }
        }

        // LED OFF
        (*LED_X[i % 3]) = !(*LED_X[i % 3]);

        //順/逆時針LED跑馬燈
        if (clockwise)
            i++;
        else
            i--;
    }
    // //release memory in heap region
    // for (int k = 0; k < 3; k++)
    //     delete LED_X[k];
}