// 判斷按鈕狀態，反應於步進馬達與LCD顯示器。
#include <LiquidCrystal_I2C.h>  //LCD_12
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  //LCD

int trigPin = 12;  //Trig Pin
int echoPin = 11;  //Echo Pin
int button_A_pin = 2;
int button_B_pin = 3;
bool button_A;
bool button_B;
int t = 5;

unsigned long timer = 0;
byte number = 0;
void rotate(bool clockwise, int degree);
void setup() {
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(button_A_pin, INPUT_PULLUP);
    pinMode(button_B_pin, INPUT_PULLUP);

    lcd.init();
    lcd.backlight();

    Serial.begin(9600);
    Serial.println();
    Serial.println("Start :");
}

void loop() {
    timer = millis();
    number = 0;
    button_A = digitalRead(button_A_pin);
    button_B = digitalRead(button_B_pin);
    while (button_A == LOW) {
        //Serial.println("press A");
        delay(50);
        button_A = digitalRead(button_A_pin);
        //counter
        if (millis() - timer > 1000) {
            number++;
            Serial.print("按壓秒數 : ");
            Serial.println(number);
            timer = millis();
            if (number >= 1000) number = 0;  //overflow
        }

        //press for 500ms
        if (button_A == HIGH) {
            Serial.println("短按A");
            rotate(true, 90);
            break;
        }

        //press for 3 seconds
        if (button_A == LOW && number > 2) {
            Serial.println("長按A");
            rotate(true, 360);
            break;
        }
    }

    while (button_B == LOW) {
        //Serial.println("press B");
        delay(50);
        button_B = digitalRead(button_B_pin);
        //counter
        if (millis() - timer > 1000) {
            number++;
            Serial.print("按壓秒數 : ");
            Serial.println(number);
            timer = millis();
            if (number >= 1000) number = 0;  //overflow
        }

        //press for 500ms
        if (button_B == HIGH) {
            Serial.println("短按B");
            rotate(false, 180);
            break;
        }

        //press for 3 seconds
        if (button_B == LOW && number > 2) {
            Serial.println("長按B");
            rotate(false, 120);
            break;
        }
    }
}

//true  -> clockwise
//false -> counterclockwise
void rotate(bool clockwise, int degree) {
    float step = degree * 5.68888;  //1 dregree = 2048/360 = 5.68888 step
    // LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("F94089032");
    lcd.setCursor(0, 1);
    lcd.print("Steps: ");
    lcd.print(round(step));
    //LCD
    
    for (int i = 0; i < 4; i++) {
        digitalWrite(i + 8, 0);
    }

    if (clockwise) {  //clockwise
        Serial.print("順時針轉");
        Serial.println(degree);
        Serial.print(round(step));
        Serial.println("步");
        Serial.println("-----------");
        for (int i = 0; i < step/4; i++) {
            digitalWrite(8, 0);
            for (int j = 3; j >= 0; j--) {
                digitalWrite(j + 8, 1);
                if (j != 3) digitalWrite(j + 1 + 8, 0);
                delay(t);
            }
        }
    } else {  //counter_clockwise
        Serial.print("逆時針轉");
        Serial.println(degree);
        Serial.print(round(step));
        Serial.println("步");
        Serial.println("-----------");
        for (int i = 0; i < step/4; i++) {
            digitalWrite(11, 0);
            for (int j = 0; j < 4; j++) {
                digitalWrite(j + 8, 1);
                if (j != 0) digitalWrite(j - 1 + 8, 0);
                delay(t);
            }
        }
    }
}
