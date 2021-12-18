// 掃描式鍵盤與七段顯示器之結合，實作碼錶。
#include <Keypad.h>
#define KEY_ROWS 4
#define KEY_COLS 4

void number_transfer(int num);
void SEG_Drive(int num);
void Letter_Drive(char L);
void stop();
void show_num();
//--------------for keypad---------------//
byte colPins[4] = {13, 9, A4, A5};
byte rowPins[4] = {A0, A1, A2, A3};
char keymap[KEY_ROWS][KEY_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};
Keypad myKeypad(makeKeymap(keymap), rowPins, colPins, KEY_ROWS, KEY_COLS);

//---------------for 7-segment---------------//
const int SEG_COM[3] = {10, 11, 12};  //控制線
const int SEG_data[10][7] = {
    //no dpsq
    {1, 1, 1, 1, 1, 1, 0},  //"0"  //資料線
    {0, 1, 1, 0, 0, 0, 0},  //"1"
    {1, 1, 0, 1, 1, 0, 1},  //"2"
    {1, 1, 1, 1, 0, 0, 1},  //"3"
    {0, 1, 1, 0, 0, 1, 1},  //"4"
    {1, 0, 1, 1, 0, 1, 1},  //"5"
    {1, 0, 1, 1, 1, 1, 1},  //"6"
    {1, 1, 1, 0, 0, 0, 0},  //"7"
    {1, 1, 1, 1, 1, 1, 1},  //"8"
    {1, 1, 1, 0, 0, 1, 1}   //"9"
};
int disp[3];  //顯示數字
int number = 0;
unsigned long timer = 0;
const int letter[2][7] = {
    {1, 1, 1, 0, 1, 1, 1},  //'A'
    {0, 0, 1, 1, 1, 1, 1}   //'B'
};

void setup() {
    //set 7-segment 3digit
    for (int i = 2; i <= 12; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, HIGH);
    }
}

void loop() {
from_start:
    char mode = myKeypad.getKey();  //choose mode
    //timer
    if (mode == 'A') {
        //display for a while
        for (int i = 0; i < 100; i++) {
            //print "AAA"
            for (int j = 0; j < 3; j++) {
                digitalWrite(SEG_COM[j], LOW);
                Letter_Drive('A');
                delay(5);
                digitalWrite(SEG_COM[j], HIGH);
            }

            number = 0;
            while (true) {
                char control_A = myKeypad.getKey();  //to control in A mode
                number_transfer(number);
                show_num();

                //add number with 1 sec
                if (millis() - timer > 1000) {
                    number++;
                    timer = millis();
                    if (number >= 1000) number = 0;  //overflow
                }

                //control is trigger
                if (control_A == 'D') {  // to stop
                    stop();
                } else if (control_A == '*') {  // to restart with A mode in 0 sec
                    number = 0;
                } else if (control_A == '#') {  //leave A mode
                    goto from_start;
                }
            }
        }
    }
    //countdown
    else if (mode == 'B') {
        //display for a while
        for (int i = 0; i < 100; i++) {
            //print "BBB"
            for (int j = 0; j < 3; j++) {
                digitalWrite(SEG_COM[j], LOW);
                Letter_Drive('B');
                delay(5);
                digitalWrite(SEG_COM[j], HIGH);
            }
        }

        //type 3-digit to start
        number = 0;
        int count = 0;
        while (count < 3) {
            char digit = myKeypad.getKey();

            if (isDigit(digit)) {                        //only digital will be valid
                number = number * 10 + int(digit) - 48;  //char(ACISII code) to int
                count++;
            }
            number_transfer(number);
            show_num();
        }
        int reset = number;  //store reset number

        while (true) {
            char start = myKeypad.getKey();
            number_transfer(number);
            show_num();

            if (start == 'C') {  //start countdown
                while (true) {
                    char control_B = myKeypad.getKey();
                    number_transfer(number);
                    show_num();

                    //minus number with 1 sec
                    if (millis() - timer > 1000) {
                        number--;
                        timer = millis();

                        if (number <= 1) break;  //overflow
                    }

                    //control_B trigger
                    if (control_B == 'D') {  // to stop
                        stop();
                    } else if (control_B == '*') {  // to restart with B mode in 0 sec
                        number = reset;
                    } else if (control_B == '#') {  //leave B mode
                        number = 0;
                        goto from_start;
                    }
                }
            }
        }
    }
    //else{} do nothing, no Led bright in 7-segment
}

////三位數拆成三個獨立的數字，存入陣列disp[]中
void number_transfer(int num) {
    for (int i = 0; i < 3; i++) {
        disp[i] = num % 10;  //取餘數
        num = num / 10;      //扣除最低位數
    }
}

void SEG_Drive(int num) {  //將字元變數從SEG_data[][]找到相對應的位置，並寫入a~g中
    for (int i = 2; i < 9; i++)
        digitalWrite(i, SEG_data[num][i - 2]);
}

void Letter_Drive(char L) {
    if (L == 'A') {
        for (int i = 2; i < 9; i++) {
            digitalWrite(i, letter[0][i - 2]);
        }
    } else if (L == 'B') {
        for (int i = 2; i < 9; i++) {
            digitalWrite(i, letter[1][i - 2]);
        }
    }
}

//stop counting
void stop() {
    while (true) {
        char start_from_stop = myKeypad.getKey();
        //show three digit
        for (int i = 0; i < 3; i++) {
            digitalWrite(SEG_COM[i], LOW);
            SEG_Drive(disp[i]);
            delay(5);
            digitalWrite(SEG_COM[i], HIGH);
        }
        if (start_from_stop == 'D') break;
    }
}

//show three digit
void show_num() {
    for (int i = 0; i < 3; i++) {
        digitalWrite(SEG_COM[i], LOW);
        SEG_Drive(disp[i]);
        delay(5);
        digitalWrite(SEG_COM[i], HIGH);
    }
}
