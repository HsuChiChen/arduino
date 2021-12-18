// 利用L298N各別控制左右2個馬達完成正轉、反轉、停止功能。

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
}

void loop() {
    if (Serial.available() > 0) {
        cmd = Serial.read();

        switch (cmd) {
            case 'w':  // 接收到'w'，前進。
                Serial.println("w");
                forward();
                run = true;  // 啟動馬達
                break;
            case 's':  // 接收到's'，後退。
                Serial.println("x");
                backward();
                run = true;  // 啟動馬達
                break;
            case 'a':  // 接收到'a'，左轉。
                Serial.println("a");
                turnLeft();
                run = true;  // 啟動馬達
                break;
            case 'd':  // 接收到'd'，右轉。
                Serial.println("d");
                turnRight();
                run = true;  // 啟動馬達
                break;
            case 'q':
                Serial.println("q");
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