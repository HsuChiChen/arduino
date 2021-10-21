#include <LiquidCrystal_I2C.h>  //LCD_12
#include <Wire.h>

void rotate(bool clockwise, int degree);
LiquidCrystal_I2C lcd(0x27, 16, 2);  //LCD

int trigPin = 12;  //Trig Pin
int echoPin = 11;  //Echo Pin
int button_pin = 2;
bool button_state;
int t = 5;
int press_count = 0;

unsigned long timer = 0;
byte number = 0;
bool before_state;
bool timeout = false;

void setup() {
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(button_pin, INPUT_PULLUP);

    lcd.init();
    lcd.backlight();

    Serial.begin(9600);
    Serial.println();
    Serial.println("Start :");
}

void loop() {
    button_state = digitalRead(button_pin);
    if (button_state == LOW && before_state == HIGH) {
        press_count++;
        Serial.print("press count : ");
        Serial.println(press_count);

        //按第一次開始計時
        if (press_count == 1) {
            timer = millis();
            //長按
            button_state = digitalRead(button_pin);
            //還是繼續按
            while (button_state == LOW) {
                button_state = digitalRead(button_pin);
                //超過3秒
                if (millis() - timer > 3000) {
                    Serial.println("press for a while");
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("long press");
                    rotate(true, 360);
                    press_count = 0;
                    break;
                }
            }
        }
    }
    if (before_state != button_state) {  //0->1 1->0 delay
        delay(20);
    }
    before_state = button_state;

    //1秒後timeout，開始計算結果
    if (millis() - timer > 1000 && press_count > 0) {
        if (press_count == 1) {
            Serial.println("press_count == 1");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("press count : ");
            lcd.print(press_count);
            rotate(true, 90);
        } else if (press_count == 2) {
            Serial.println("press_count == 2");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("press count : ");
            lcd.print(press_count);
            rotate(true, 120);
        } else if (press_count == 3) {
            Serial.println("press_count == 3");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("press count : ");
            lcd.print(press_count);
            rotate(true, 180);
        } else {
            Serial.println("Out of condition");
        }
        press_count = 0;
    }
}

//true  -> clockwise
//false -> counterclockwise
void rotate(bool clockwise, int degree) {
    float step = degree * 5.68888;  //1 dregree = 2048/360 = 5.68888 step
    // LCD
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
        for (int i = 0; i < step / 4; i++) {
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
        for (int i = 0; i < step / 4; i++) {
            digitalWrite(11, 0);
            for (int j = 0; j < 4; j++) {
                digitalWrite(j + 8, 1);
                if (j != 0) digitalWrite(j - 1 + 8, 0);
                delay(t);
            }
        }
    }
}
