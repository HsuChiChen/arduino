// 利用2個超聲波模組測方位，當物體在50公分內，將測得方位(前、左、右、太近)顯示於LCD上。
#include <LiquidCrystal_I2C.h>  //LCD_12
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  //LCD

int echo_left = 8;    //Echo Pin
int trig_left = 9;     //Trig Pin
int echo_right = 10;  //Echo Pin
int trig_right = 11;   //Trig Pin
long duration_left, duration_right, cm_left, cm_right;

void setup() {
    Serial.begin(9600);       // Serial Port begin
    pinMode(trig_left, OUTPUT);
    pinMode(trig_right, OUTPUT);
    pinMode(echo_left, INPUT);
    pinMode(echo_right, INPUT);
    lcd.init();
    lcd.backlight();
    lcd.clear();
    Serial.println("Start");
}

void loop() {
    //fist HC-SR04
    digitalWrite(trig_left, LOW);
    delayMicroseconds(5);
    digitalWrite(trig_left, HIGH);  // 給 Trig 高電位，持續10微秒
    delayMicroseconds(10);
    digitalWrite(trig_left, LOW);

    pinMode(echo_left, INPUT);            // 讀取 echo 的電位
    duration_left = pulseIn(echo_left, HIGH);  // 收到高電位時的時間
    cm_left = (duration_left / 2) / 29.1;  // 將時間換算成距離 cm 或 inch
    Serial.print("cm_left  : ");
    Serial.println(cm_left);

    //second HC-SR04
    digitalWrite(trig_right, LOW);
    delayMicroseconds(5);
    digitalWrite(trig_right, HIGH);  // 給 Trig 高電位，持續10微秒
    delayMicroseconds(10);
    digitalWrite(trig_right, LOW);

    pinMode(echo_right, INPUT);            // 讀取 echo 的電位
    duration_right = pulseIn(echo_right, HIGH);  // 收到高電位時的時間
    cm_right = (duration_right / 2) / 29.1;  // 將時間換算成距離 cm 或 inch
    Serial.print("cm_right : ");
    Serial.println(cm_right);
    Serial.println("--------------------");

    if (cm_left < 10 && cm_right < 10) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("too close");
    } else if (cm_left < 50 && cm_right < 50 && abs(cm_right-cm_left)<=25) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("straight");
    }  //超音波1在左邊，向右探測
    else if (cm_left < 50 && cm_right > 50 && ) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("right");
    } else if (cm_left > 50 && cm_right < 50) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("left");
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("none of object");
    }
    delay(800);
}
