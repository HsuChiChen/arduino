// 實現碼錶。使用七段顯示器顯示秒數，秒數精準到小數2位，秒數為個位數時，不顯示十位數數字。
// |按鈕|功能|
// |:--:|:--:|
// |短按|停止/開始|
// |長按|歸零並停止|

#include "mbed.h"

void show_digit();
void number_transfer(int);
void SEG_Drive(int);

DigitalOut *SEG_COM[4];  //control
DigitalOut *digit[8];    //each 7-seg
Timer timer;             // timer
Timer timer2;
RawSerial pc(USBTX, USBRX);  //display on serial monitor

int t_10ms;
const int SEG_data[10][8] = {   //資料線
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
int disp[4];                    //欲顯示數字

int main() {
    // state boolean value
    bool object_exist = false;
    bool short_press = false;
    bool counting = true;
    bool count_once = false;

    // intialize pin
    SEG_COM[0] = new DigitalOut(D10);
    SEG_COM[1] = new DigitalOut(D11);
    SEG_COM[2] = new DigitalOut(D12);

    digit[0] = new DigitalOut(D2);
    digit[1] = new DigitalOut(D3);
    digit[2] = new DigitalOut(D4);
    digit[3] = new DigitalOut(D5);
    digit[4] = new DigitalOut(D6);
    digit[5] = new DigitalOut(D7);
    digit[6] = new DigitalOut(D8);
    digit[7] = new DigitalOut(D9);  // dp

    // button setting
    DigitalIn button(USER_BUTTON);  //the button on your board
    if (button.is_connected())
        pc.printf("button is connected and initialized! \n\r");
    button.mode(PullNone);  //浮接

    //stopped 0
    while (1) {
        show_digit();
        if (button.read()) break;
    }

    //timer start counting
    timer.start();
    wait(0.1);

    while (1) {
        // update 7-seg value
        t_10ms = (timer.read_ms()) / 10;
        show_digit();

        // 等到10秒以後才會新建這個class的對象
        // 否則如果一開始新增對象，而不給值，會造成這個對象接口是未知的數字，而顯示亂碼。
        if (t_10ms > 999 && object_exist == false) {
            pc.printf("new MSB object\n\r");
            SEG_COM[3] = new DigitalOut(D13);
            object_exist = true;
        }

        //overflow
        if (t_10ms > 9999) {
            pc.printf("delete all of object\n\r");
            for (int i = 0; i < 3; i++)
                delete SEG_COM[i];
            for (int i = 0; i < 8; i++)
                delete digit[i];
            break;
        }

        //button control
        count_once = false;
        while (button.read()) {
            // exe once
            if (count_once == false) {
                timer2.reset();  // 歸零
                timer2.start();  // 開始記數
                count_once = true;
            }
            // short_press flg
            short_press = true;

            // update 7-seg value
            t_10ms = (timer.read_ms()) / 10;
            show_digit();

            //長按歸零
            if (timer2.read() >= 1.5) {
                pc.printf("reset for long press\n\r");
                short_press = false;
                timer.reset();
                timer.stop();
                //delete MSB object
                if (object_exist == true) {
                    delete SEG_COM[3];
                    object_exist = false;
                    pc.printf("delete MSB object\n\r");
                }
                while (1) {
                    // update 7-seg value
                    t_10ms = (timer.read_ms()) / 10;
                    show_digit();
                    // release button
                    if (!button.read()) {
                        timer.start();
                        break;
                    }
                }
                break;
            }
        }

        //reaction of short press
        if (short_press == true) {
            short_press = false;
            if (counting == true) {
                timer.stop();
                counting = false;
                pc.printf("stop for short press\n\r");
            } else {
                timer.start();
                counting = true;
                pc.printf("restart for short press\n\r");
            }
        }
    }
}

void show_digit() {
    number_transfer(t_10ms);
    int init = (t_10ms <= 999) ? 3 : 4;
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
void number_transfer(int num) {  //三位數拆成三個獨立的數字，存入陣列disp[]中
    for (int i = 0; i < 4; i++) {
        disp[i] = num % 10;  //取餘數
        num = num / 10;
    }
}
void SEG_Drive(int number) {  //將字元變數從SEG_data[][]找到相對應的位置，並寫入a~g中
    for (int i = 0; i < 7; i++)
        (*digit[i]).write(SEG_data[number][i]);
}