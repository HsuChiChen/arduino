#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11);  // 宣告10腳位為Arduino的RX 、11為Arduino的 TX
char val = '1';                         //儲存接受到的資料變數

void number_transfer(int num);
void SEG_Drive(int num);

// 控制多工七段顯示器，每隔一秒計數加一
const int SEG_COM[4] = {A0, A1, A2, A3};  //控制線
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
int disp[4];                    //顯示數字
int number = 0;
unsigned long timer = 0;

void setup() {
    Serial.begin(9600);
    BTSerial.begin(38400);  //注意，HC-05要設定成38400

    for (int i = 2; i <= 9; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, HIGH);  //共陽極
    }
    for (int i = 14; i <= 17; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, HIGH);  //共陽極
    }


}
void loop() {
    // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
    if (Serial.available()) {
        val = Serial.read();
        BTSerial.print(val);
    }

    // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
    if (BTSerial.available()) {
        val = BTSerial.read();
        Serial.print(val);
    }

    //--------conunt_number-----------------
    number_transfer(number);  //數值轉換入陣列中(number -> disp[4])

    //show four digit
    for (int i = 0; i < 4; i++) {
        digitalWrite(SEG_COM[i], LOW);  //觸發第i位數顯示數字 //選擇要讓哪個七段顯示器亮
        SEG_Drive(disp[i]);
        delay(5);
        digitalWrite(SEG_COM[i], HIGH);
    }

    //add number with 0.1 sec
    if (millis() - timer > 100) {
        number++;
        timer = millis();

        if (number >= 10000) number = 0;  //overflow
    }

    //press 0, return 0
    if (val == '0') {
        number = 0;
    }

    if (val == '1') {
        while (true) {
            for (int i = 0; i < 4; i++) {
                digitalWrite(SEG_COM[i], LOW);  //觸發第i位數顯示數字 //選擇要讓哪個七段顯示器亮
                SEG_Drive(disp[i]);
                delay(5);
                digitalWrite(SEG_COM[i], HIGH);
            }

            if (BTSerial.available()) {
              val = BTSerial.read();
                if (val == '1') {
                    val = '2';
                    break;
                }
                if (val == '0') {
                    number = 0;
                    val = '2';
                    break;
                }
            }
        }
    }

    //--------conunt_number-----------------
}

//4位數拆成4個獨立的數字，存入陣列disp[]中
void number_transfer(int num) {
    for (int i = 0; i < 4; i++) {
        disp[i] = num % 10;  //取餘數 (0取餘數還是0)
        num = num / 10;      //扣除最低位數(當數字為1時，則為0)
    }
}

//選擇要亮數字0-9
void SEG_Drive(int num) {  //將字元變數從SEG_data[][]找到相對應的位置，並寫入a~g中
    for (int i = 2; i < 10; i++)
        digitalWrite(i, SEG_data[num][i - 2]);
}
