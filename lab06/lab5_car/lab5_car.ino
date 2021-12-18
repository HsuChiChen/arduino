// 利用藍牙模組HC-05，結合lab4跟隨自走車，實作遙控車。
#include <SoftwareSerial.h>
// 定義連接藍牙模組的序列埠
SoftwareSerial BT(10, 11);  // 接收腳, 傳送腳
// 接收序列埠值的變數
char cmd;
// 設定啟動或停止馬達的參數
// 一開始先設定成「停止」
boolean run = false;

// 左馬達控制設定
const byte LEFT1 = 2;     //In1
const byte LEFT2 = 4;     //In2
const byte LEFT_PWM = 3;  //ENA

// 右馬達控制設定
const byte RIGHT1 = 6;     //In3
const byte RIGHT2 = 7;     //In4
const byte RIGHT_PWM = 5;  //ENB

// 設定PWM輸出值
byte motorSpeed = 150;

void forward() {  // 馬達轉向：前進
    Serial.println("forward");
    digitalWrite(LEFT1, HIGH);
    digitalWrite(LEFT2, LOW);
    digitalWrite(RIGHT1, HIGH);
    digitalWrite(RIGHT2, LOW);
}

void backward() {  // 馬達轉向：後退
    Serial.println("backward");
    digitalWrite(LEFT1, LOW);
    digitalWrite(LEFT2, HIGH);
    digitalWrite(RIGHT1, LOW);
    digitalWrite(RIGHT2, HIGH);
}

void turnLeft() {  // 馬達轉向：左轉 1反2正
    Serial.println("turnLeft");
    digitalWrite(LEFT1, LOW);
    digitalWrite(LEFT2, HIGH);
    digitalWrite(RIGHT1, HIGH);
    digitalWrite(RIGHT2, LOW);
}

void turnRight() {  // 馬達轉向：右轉 1正2反
    Serial.println("turnRight");
    digitalWrite(LEFT1, HIGH);
    digitalWrite(LEFT2, LOW);
    digitalWrite(RIGHT1, LOW);
    digitalWrite(RIGHT2, HIGH);
}

void setup() {
    Serial.begin(9600);
    pinMode(LEFT1, OUTPUT);
    pinMode(LEFT2, OUTPUT);
    pinMode(LEFT_PWM, OUTPUT);
    pinMode(RIGHT1, OUTPUT);
    pinMode(RIGHT2, OUTPUT);
    pinMode(RIGHT_PWM, OUTPUT);
    Serial.println();
    Serial.println("Start :");
    // 設定藍牙模組的連線速率
    BT.begin(38400);
}

void loop() {
    // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
    if (BT.available()) {
        cmd = BT.read();
        switch (cmd) {
            case 'w':case 'f':  // 接收到'f'，前進。
                Serial.println("f");
                forward();
                run = true;  // 啟動馬達
                break;
            case 's':case 'b':  // 接收到'b'，後退。
                Serial.println("b");
                backward();
                run = true;  // 啟動馬達
                break;
            case 'a':case 'l':  // 接收到'l'，左轉。
                Serial.println("l");
                turnLeft();
                run = true;  // 啟動馬達
                break;
            case 'd':case 'r':  // 接收到'r'，右轉。
                Serial.println("r");
                turnRight();
                run = true;  // 啟動馬達
                break;
            case 'q':
                Serial.println("s");
                run = false;  // 停止馬達
                break;
            default:
                Serial.println("no action");
                break;
        }
    }

    if (run) {
        // 如果要啟動馬達…
        // 向馬達輸出指定的類比電壓值
        analogWrite(LEFT_PWM, motorSpeed);
        analogWrite(RIGHT_PWM, (motorSpeed+30));
    } else {
        // 否則…
        // 將馬達的電壓值設定成0
        analogWrite(LEFT_PWM, 0);
        analogWrite(RIGHT_PWM, 0);
    }
}
