// 控制多工七段顯示器顯示"2021"。
const int SEG_COM[4] = {10, 11, 12, 13};  //控制線
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

int display[4] = {2, 0, 2, 1};  //欲顯示數字

void setup() {
    for (int i = 2; i <= 13; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, HIGH);  //共陽極所有LED高電壓都相連，故另一端設為高電壓，LED則不會亮
    }
}

void loop() {
    for (int i = 0; i <= 3; i++) {      //個、十、百、千位數
        digitalWrite(SEG_COM[i], LOW);  //觸發第i位數顯示數字 //選擇要讓哪個七段顯示器亮
        SEG_Drive(display[3-i]);          //資料線寫入數值
        delay(5);
        digitalWrite(SEG_COM[i], HIGH);  //結束觸發第i位數
    }
}

//選擇要亮數字0-9
void SEG_Drive(int number) {  //將字元變數從SEG_data[][]找到相對應的位置，並寫入a~g中
    for (int i = 2; i < 9; i++)
        digitalWrite(i, SEG_data[number][i - 2]);
}