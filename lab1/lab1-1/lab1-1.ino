// 5個GPIO的呈現燈亮從左到右的跑馬燈狀態
int Led[5] = {8, 9, 10, 11, 12};

// put your setup code here, to run once:
void setup() {
    for (int i = 0; i < 5; i++)
        pinMode(Led[i], OUTPUT);  //預設接口為INPUT，故只需設定OUTPUT接口
}

// put your main code here, to run repeatedly:
void loop() {
    for (int i = 0; i < 5; i++) {
        digitalWrite(Led[i], HIGH);  //兩端電壓高到低->LED通電
        delay(200);
        digitalWrite(Led[i], LOW);  //兩端電壓皆為低->LED通電
        delay(100);
    }
}