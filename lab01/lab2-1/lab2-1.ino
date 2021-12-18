// 按上拉電阻的Button時，LED向左一顆亮；按下拉電阻的Button時，LED向右邊一顆亮。
const int Led[5] = {8, 9, 10, 11, 12};  //LED
const int sw_up = 2;                    //按鈕1
const int sw_down = 3;                  //按鈕2
int pos = 2;                            //初始亮LED位置

void setup() {
    for (int i = 0; i < 5; i++) {
        pinMode(Led[i], OUTPUT);    //設OUTPUT腳位
        digitalWrite(Led[i], LOW);  //初始化關閉LED
    }
    digitalWrite(Led[2], HIGH);
    pinMode(sw_up, INPUT_PULLUP);  //內建上拉電阻
    pinMode(sw_down, INPUT);       //下拉電阻(需由使用者自行硬體實踐)
}

void loop() {
    bool swstate_up = digitalRead(sw_up);
    bool swstate_down = digitalRead(sw_down);

    if (swstate_up == LOW) {
        digitalWrite(Led[pos], LOW);
        pos = (pos == 4) ? 0 : pos + 1;  //三元運算符 ans = (condtion)?true : flase
        digitalWrite(Led[pos], HIGH);
        delay(500);
    } else if (swstate_down == HIGH) {
        digitalWrite(Led[pos], LOW);
        pos = (pos == 0) ? 4 : pos - 1;
        digitalWrite(Led[pos], HIGH);
        delay(500);
    }
}
