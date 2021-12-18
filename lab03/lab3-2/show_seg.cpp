#include "show_seg.h"

SHOW_SEG::SHOW_SEG(int first_pin, int last_pin, int cfirst_pin, int clast_pin) {
    this->first_pin = first_pin;
    this->last_pin = last_pin;
    this->cfirst_pin = cfirst_pin;
    this->clast_pin = clast_pin;
    init();
}

void SHOW_SEG::init() {
    for (int i = first_pin; i <= last_pin; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, HIGH);  //共陽極所有LED高電壓都相連，故另一端設為高電壓，LED則不會亮
    }

    for (int i = cfirst_pin; i <= clast_pin; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, HIGH);  //共陽極所有LED高電壓都相連，故另一端設為高電壓，LED則不會亮
    }
}

void SHOW_SEG::show(int num) {
    number_transfer(num);
    show_digit();
}

void SHOW_SEG::number_transfer(int num) {
    for (int i = 0; i < 3; i++) {
        this->display[i] = num % 10;  //取餘數
        num = num / 10;               //扣除最低位數
    }
}

void SHOW_SEG::show_digit() {
    const int SEG_COM[4] = {A0, A1, A2, A3};  //控制線

    for (int i = 0; i <= 3; i++) {      //個、十、百、千位數
        digitalWrite(SEG_COM[i], LOW);  //觸發第i位數顯示數字 //選擇要讓哪個七段顯示器亮
        SEG_Drive(this->display[i]);    //資料線寫入數值
        delay(5);
        digitalWrite(SEG_COM[i], HIGH);  //結束觸發第i位數
    }
}

//選擇要亮數字0-9
void SHOW_SEG::SEG_Drive(int number) {  //將字元變數從SEG_data[][]找到相對應的位置，並寫入a~g中
    const int SEG_data[10][8] = {
        {1, 1, 1, 1, 1, 1, 0, 0},   //"0"  //資料線
        {0, 1, 1, 0, 0, 0, 0, 0},   //"1"
        {1, 1, 0, 1, 1, 0, 1, 0},   //"2"
        {1, 1, 1, 1, 0, 0, 1, 0},   //"3"
        {0, 1, 1, 0, 0, 1, 1, 0},   //"4"
        {1, 0, 1, 1, 0, 1, 1, 0},   //"5"
        {1, 0, 1, 1, 1, 1, 1, 0},   //"6"
        {1, 1, 1, 0, 0, 0, 0, 0},   //"7"
        {1, 1, 1, 1, 1, 1, 1, 0},   //"8"
        {1, 1, 1, 0, 0, 1, 1, 0}};  //"9"
    for (int i = 2; i < 9; i++)
        digitalWrite(i, SEG_data[number][i - 2]);
}