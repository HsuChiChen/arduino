// 控制多工七段顯示器，每隔一秒計數加一。
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
int disp[4];                    //顯示數字
int number = 0;
unsigned long timer = 0;

void setup() {
    for (int i = 2; i <= 13; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, HIGH);  //共陽極
    }
}

void loop() {
    number_transfer(number);  //數值轉換入陣列中(number -> disp[4])

    //show four digit
    for (int i = 0; i < 4; i++) {
        digitalWrite(SEG_COM[i], LOW); //觸發第i位數顯示數字 //選擇要讓哪個七段顯示器亮
        SEG_Drive(disp[i]);
        delay(5);
        digitalWrite(SEG_COM[i], HIGH);
    }

    //add number with 1 sec
    if (millis() - timer > 1000) {
        number++;
        timer = millis();

        if (number >= 10000) number = 0;  //overflow
    }
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
