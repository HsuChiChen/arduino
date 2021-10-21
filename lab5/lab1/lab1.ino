#include <LiquidCrystal_I2C.h>  //LCD_12
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  //LCD

int trigPin = 12;  //Trig Pin
int echoPin = 11;  //Echo Pin
int LED = 2;
long duration, cm, inches;

void setup() {
    Serial.begin(9600);        // Serial Port begin
    pinMode(trigPin, OUTPUT);  // 定義輸入及輸出
    pinMode(echoPin, INPUT);
    pinMode(LED, OUTPUT);

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
    inches = (duration / 2) / 74;

    Serial.print("Distance : ");
    Serial.print(inches);
    Serial.print("in,   ");
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();

    //control LCD
    if (cm <= 20) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("F94089032");
        lcd.setCursor(0, 1);
        lcd.print("Distance: ");
        lcd.print(cm);
        lcd.print(" cm");
    } else {
        lcd.clear();
        lcd.print("Out of Distance");
    }

    //control LED
    if (cm <= 5) {
        digitalWrite(LED, HIGH);
    } else {
        digitalWrite(LED, HIGH);
        delay(cm * 20);
        digitalWrite(LED, LOW);
    }

    delay(250);
}
