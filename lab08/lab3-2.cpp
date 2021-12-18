// 一開始跑馬燈順序GBRA，USER_BUTTON長按進入在serial monitor上輸入指令狀態，
// 接著透過輸入R,G,B,A(外接的LED)的不同排列順序改變起始亮燈順序，
// 須有輸入的錯誤偵測，並在按下Enter後回到跑馬燈順序GBRA。

#include "mbed.h"
RawSerial pc(USBTX, USBRX);  // tx, rx

int main() {
    //input參數
    int order[4];
    DigitalIn button(USER_BUTTON);  //the button on your board
    if (button.is_connected())
        pc.printf("\rbutton is connected and initialized!\n\rPress the user button to enter cmd mode.\r\n");
    button.mode(PullNone);  //浮接

    //output參數
    DigitalOut *X[4];  //創建DigitalOut屬性指標陣列
    //在heap區開闢DigitalOut類的匿名對象，並將她的位置存進在stack區的指標陣列
    X[0] = new DigitalOut(LED1);
    X[1] = new DigitalOut(LED2);
    X[2] = new DigitalOut(LED3);
    X[3] = new DigitalOut(PD_7);

    while (1) {
        int counter = 0;
        int i = 0;
        while (1) {
            i = counter % 4;
            *X[i] = !*X[i];
            wait(0.5);
            *X[i] = !*X[i];
            wait(0.5);
            counter++;
            //當按下按鈕時，離開迴圈
            if (button.read()) {
                pc.printf("Enter the blinking order of LED (R,G,B,A)\n\r");
                break;
            }
        }
        counter = 0;
        char cmd;
        while (counter < 4) {
            cmd = pc.getc();

            switch (cmd) {
                case 'G':
                    pc.putc(cmd);  // echo input back to terminal
                    order[counter++] = 0;
                    break;
                case 'B':
                    pc.putc(cmd);  // echo input back to terminal
                    order[counter++] = 1;
                    break;
                case 'R':
                    pc.putc(cmd);  // echo input back to terminal
                    order[counter++] = 2;
                    break;
                case 'A':
                    pc.putc(cmd);  // echo input back to terminal
                    order[counter++] = 3;
                    break;
                default:
                    pc.printf("\n\rInvalid input! Please enter again\n\r");
                    counter = 0;
                    break;
            }
        }

        pc.printf("\n\rThe order your enter success\n\r");

        counter = 0;
        while (1) {
            i = counter % 4;           //[0, 1, 2, 3]
            int led_order = order[i];  //get order from array value
            printf("led_order [%d] = %d\r\n", i, led_order);

            *X[led_order] = !*X[led_order];
            wait(0.5);
            *X[led_order] = !*X[led_order];
            wait(0.5);
            counter++; // 0,1,2,3 increasing

            if (pc.readable()) {
                cmd = pc.getc();
                if (cmd == '\r') {
                    pc.printf("Back to initial setting\r\nPress the user button to enter cmd mode.\r\n");
                    while (pc.readable()) //clean buffer
                        pc.getc();
                    break;
                }
            }
        }
    }

    // //release memory in heap region
    // for (int k = 0; k < 4; k++)
    //     delete X[k];
}