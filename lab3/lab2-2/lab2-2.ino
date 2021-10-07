#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11);
int LED[5] = {2, 3, 4, 5, 6};

char val;
char b_val;
char condition;
bool LED_state = LOW;
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
    } else if (val == '1') {
        Serial.println("mode 1");
        while (true) {
            for (int i = 0; i < 5; i++) {
                digitalWrite(LED[i], HIGH);  //兩端電壓高到低->LED通電
                delay(200);
                digitalWrite(LED[i], LOW);  //兩端電壓皆為低->LED通電
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
    } else if (val == '3') {
        Serial.println("mode 3");
        while (true) {
            for (int i = 0; i < 2; i++) {
                if (i == 0) {
                    for (int num = 6; num < 2; num--) {
                        LED_state = HIGH;
                        digitalWrite(LED[num], LED_state);
                        delay(300);
                    }
                } else {
                    for (int num = 2; num < 7; num++) {
                        digitalWrite(LED[num], LOW);
                        delay(300);
                    }
                }
            }
            while (true) {
                if (Serial.available()) {
                    val = Serial.read();
                    BTSerial.println(val);
                    break;
                }
            }
        }
    } else if (val == '4') {
    } else {
    }

    // bluetooth pass
    if (BTSerial.available()) {
        b_val = BTSerial.read();
        //Serial.print(val);
    }
    delay(100);
}