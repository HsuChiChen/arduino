// 當距離越近，duty cycle越高。
#include <LiquidCrystal_I2C.h>  //LCD_12
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  //LCD

int trigPin = 12;  //Trig Pin
int echoPin = 11;  //Echo Pin
int analog = 3;
long duration, cm;
int duty_cycle;

void setup() {
    Serial.begin(9600);        // Serial Port begin
    pinMode(trigPin, OUTPUT);  // 定義輸入及輸出
    pinMode(echoPin, INPUT);
    lcd.init();
    lcd.backlight();
    lcd.clear();
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

    duty_cycle = 255 - (255 / 20) * cm;  //0->255 20->0
    analogWrite(analog, duty_cycle);
    Serial.print("Distance : ");
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("F94089032");
    lcd.setCursor(0, 1);
    lcd.print("Distance: ");
    lcd.print(cm);
    lcd.print(" cm");
    delay(250);
}
