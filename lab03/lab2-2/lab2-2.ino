// Serial Monitor上輸入再透過藍芽傳資料，控制五顆LED跑馬燈。
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11);
int LED[5] = {2, 3, 4, 5, 6};

char val;
char b_val;
char condition;
bool led[5] = {0};
bool exe_once = false;
void setup() {
    Serial.begin(9600);
    BTSerial.begin(38400);
    for (int i = 0; i < 5; i++) {
        pinMode(LED[i], OUTPUT);
    }

    while (!exe_once) {
        if (Serial.available()) {
            Serial.println("set");
            val = Serial.read();
            BTSerial.println(val);
            exe_once = true;
        }
    }
}

void loop() {
    //--------------Serial -> bluetooth-------------------//

    if (val == '0') {
        Serial.println("mode 0");
        while (true) {
            for (int i = 0; i < 5; i++)
                digitalWrite(LED[i], led[i]);
            if (Serial.available()) {
                val = Serial.read();
                Serial.println(val);
                BTSerial.println(val);
                break;
            }
        }
    } else if (val == '1') {
        Serial.println("mode 1");
        while (true) {
            for (int i = 0; i < 5; i++) {
                digitalWrite(LED[i], HIGH);
                digitalWrite(led[i], HIGH);
                delay(200);
                digitalWrite(LED[i], LOW);
                digitalWrite(led[i], LOW);
                delay(100);
            }
            if (Serial.available()) {
                val = Serial.read();
                Serial.println(val);
                BTSerial.println(val);
                break;
            }
        }
    } else if (val == '2') {
        Serial.println("mode 2");
        while (true) {
            for (int i = 0; i < 5; i = i + 2) {
                digitalWrite(LED[i], HIGH);  //兩端電壓高到低->LED通電
                digitalWrite(led[i], HIGH);
                delay(200);
                digitalWrite(LED[i], LOW);  //兩端電壓皆為低->LED通電
                digitalWrite(led[i], LOW);
                delay(100);
            }
            for (int i = 1; i < 5; i = i + 2) {
                digitalWrite(LED[i], HIGH);  //兩端電壓高到低->LED通電
                digitalWrite(led[i], HIGH);
                delay(200);
                digitalWrite(LED[i], LOW);  //兩端電壓皆為低->LED通電
                digitalWrite(led[i], LOW);
                delay(100);
            }
            if (Serial.available()) {
                val = Serial.read();
                Serial.println(val);
                BTSerial.println(val);
                break;
            }
        }
    } else if (val == '3') {
        Serial.println("mode 3");
        for (int i = 0; i < 2; i++) {
            if (i == 0) {
                for (int num = 4; num >= 0; num--) {
                    digitalWrite(LED[num], HIGH);
                    digitalWrite(led[num], HIGH);
                    delay(100);
                }
            } else {
                for (int num = 0; num < 5; num++) {
                    digitalWrite(LED[num], LOW);
                    digitalWrite(led[num], LOW);
                    delay(100);
                }
            }
            if (Serial.available()) {
                val = Serial.read();
                Serial.println(val);
                BTSerial.println(val);
                break;
            }
        }
    } else if (val == '4') {
        Serial.println("mode 4");
        while (true) {
            for (int i = 0; i < 5; i++) {
                digitalWrite(LED[i], HIGH);
                digitalWrite(led[i], HIGH);
            }
            if (Serial.available()) {
                val = Serial.read();
                Serial.println(val);
                BTSerial.println(val);
                break;
            }
        }
    } else {
        Serial.println("mode else");
        while (true) {
            for (int i = 0; i < 5; i++) {
                digitalWrite(LED[i], HIGH);
                digitalWrite(led[i], HIGH);
            }
            delay(200);
            for (int i = 0; i < 5; i++) {
                digitalWrite(LED[i], LOW);
                digitalWrite(led[i], LOW);
            }
            delay(100);

            if (Serial.available()) {
                val = Serial.read();
                Serial.println(val);
                BTSerial.println(val);
                break;
            }
        }
    }

    delay(100);
}
