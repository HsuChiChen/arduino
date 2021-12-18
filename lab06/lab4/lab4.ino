// 利用2個超音波模組、L298N驅動馬達，實作跟隨自走車。
//HC-SR04
int echo_left = 14;   //Echo Pin
int trig_left = 15;   //Trig Pin
int echo_right = 16;  //Echo Pin
int trig_right = 17;  //Trig Pin
long duration_left, duration_right, cm_left, cm_right;

// 左馬達控制設定
const byte LEFT1 = 2;     //IN1
const byte LEFT2 = 4;     //IN2
const byte LEFT_PWM = 3;  //ENA

// 右馬達控制設定
const byte RIGHT1 = 6;     //IN3
const byte RIGHT2 = 7;     //IN4
const byte RIGHT_PWM = 5;  //ENB

// 設定PWM輸出值
byte motor_speed = 150;

void forward() {  // 馬達轉向：前進
    digitalWrite(LEFT1, HIGH);
    digitalWrite(LEFT2, LOW);
    digitalWrite(RIGHT1, HIGH);
    digitalWrite(RIGHT2, LOW);
    motor_speed = 150;
}

void backward() {  // 馬達轉向：後退
    digitalWrite(LEFT1, LOW);
    digitalWrite(LEFT2, HIGH);
    digitalWrite(RIGHT1, LOW);
    digitalWrite(RIGHT2, HIGH);
    motor_speed = 150;
}

void turnLeft() {  // 馬達轉向：左轉 1反2正
    digitalWrite(LEFT1, LOW);
    digitalWrite(LEFT2, LOW);
    digitalWrite(RIGHT1, HIGH);
    digitalWrite(RIGHT2, LOW);
    motor_speed = 100;
}

void turnRight() {  // 馬達轉向：右轉 1正2反
    digitalWrite(LEFT1, HIGH);
    digitalWrite(LEFT2, LOW);
    digitalWrite(RIGHT1, LOW);
    digitalWrite(RIGHT2, LOW);
    motor_speed = 100;
}

void setup() {
    Serial.begin(9600);
    pinMode(LEFT1, OUTPUT);
    pinMode(LEFT2, OUTPUT);
    pinMode(LEFT_PWM, OUTPUT);
    pinMode(RIGHT1, OUTPUT);
    pinMode(RIGHT2, OUTPUT);
    pinMode(RIGHT_PWM, OUTPUT);

    //HC-SR04
    pinMode(trig_left, OUTPUT);
    pinMode(trig_right, OUTPUT);
    pinMode(echo_left, INPUT);
    pinMode(echo_right, INPUT);
}

void loop() {
    //fist HC-SR04
    digitalWrite(trig_left, LOW);
    delayMicroseconds(5);
    digitalWrite(trig_left, HIGH);  // 給 Trig 高電位，持續10微秒
    delayMicroseconds(10);
    digitalWrite(trig_left, LOW);

    pinMode(echo_left, INPUT);                 // 讀取 echo 的電位
    duration_left = pulseIn(echo_left, HIGH);  // 收到高電位時的時間
    cm_left = (duration_left / 2) / 29.1;      // 將時間換算成距離 cm 或 inch

    //second HC-SR04
    digitalWrite(trig_right, LOW);
    delayMicroseconds(5);
    digitalWrite(trig_right, HIGH);  // 給 Trig 高電位，持續10微秒
    delayMicroseconds(10);
    digitalWrite(trig_right, LOW);

    pinMode(echo_right, INPUT);                  // 讀取 echo 的電位
    duration_right = pulseIn(echo_right, HIGH);  // 收到高電位時的時間
    cm_right = (duration_right / 2) / 29.1;      // 將時間換算成距離 cm 或 inch

    Serial.print("Right: ");
    Serial.println(cm_right);
    Serial.print("Left : ");
    Serial.println(cm_left);
    Serial.println("----------");
    Serial.println();
    if (cm_right < 20 && cm_left < 20) {  // "go back"
        Serial.println("back");
        backward();
    } else if (cm_right > (cm_left + 30) && cm_left < 50) {  //"turn right"
        Serial.println("right");
        turnRight();
    } else if (cm_left > (cm_right + 10) && cm_right < 50) {  //"turn left"
        Serial.println("left");
        turnLeft();
    } else if ((cm_left < 100 || cm_right < 100) && abs(cm_right - cm_left) <= 10) {  //"go straight"
        Serial.println("straight");
        forward();
    } else {  //"stop"
        Serial.println("stop");
        motor_speed = 0;
    }

    // 向馬達輸出指定的類比電壓值
    analogWrite(LEFT_PWM, motor_speed);
    analogWrite(RIGHT_PWM, motor_speed + 30);
    // 實際上給定PWM，2端輪子轉速不一致，因此需要有offset = 30的誤差修正
    delay(100);
}
