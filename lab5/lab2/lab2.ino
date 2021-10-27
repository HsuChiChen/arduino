// 使用步進馬達搭配LCD顯示器與按鈕。
int trigPin = 13;  //Trig Pin
int echoPin = 12;  //Echo Pin
long duration, cm;

int t = 3;  //換相所需的時間
void rotate(int mode);
void setup() {
    Serial.begin(9600);        // Serial Port begin
    pinMode(trigPin, OUTPUT);  // 定義輸入及輸出
    pinMode(echoPin, INPUT);

    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
}
void loop() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);  // 給 Trig 高電位，持續 10微秒
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    pinMode(echoPin, INPUT);            // 讀取 echo 的電位
    duration = pulseIn(echoPin, HIGH);  // 收到高電位時的時間

    cm = (duration / 2) / 29.1;  // 將時間換算成距離 cm 或 inch

    Serial.print("Distance : ");
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();

    if (cm <= 10)
        rotate(0);
    else if (cm >= 15)
        rotate(1);
    else
        rotate(2);
}

void rotate(int mode) {
    for (int i = 0; i < 4; i++) {
        digitalWrite(i + 8, 0);
    }

    if (mode == 0) {  //clockwise
        for (int i = 3; i >= 0; i--) {
            digitalWrite(i + 8, 1);
            if (i != 3) digitalWrite(i + 1 + 8, 0);
            delay(t);
        }
    }
    if (mode == 1) {  //counter_clockwise
        for (int i = 0; i < 4; i++) {
            digitalWrite(i + 8, 1);
            if (i != 0) digitalWrite(i - 1 + 8, 0);
            delay(t);
        }
    }
    if (mode == 2) {  //stop
        for (int i = 0; i < 4; i++) {
            digitalWrite(i + 8, 0);
        }
    }
}
