// Serial Monitor上輸入再透過藍芽傳資料，來控制LED亮暗。
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11);
#define LED 12

char val;
bool LED_state = LOW;

void setup() {
    Serial.begin(9600);
    BTSerial.begin(38400);
    pinMode(LED, OUTPUT);
}

void loop() {
    //Serial -> bluetooth
    if (Serial.available()) {
        val = Serial.read();
        // Serial.println(int(val));  //test for 換行
        BTSerial.write(val);
    }
    // bluetooth pass
    if (BTSerial.available()) {
        val = BTSerial.read();
        //Serial.print(val);

        if (val == '1') {
            Serial.println("HIGH");
            LED_state = HIGH;
            digitalWrite(LED, LED_state);
        } else if (val == '0') {
            Serial.println("LOW");
            LED_state = LOW;
            digitalWrite(LED, LED_state);
        } else {
            for (int i = 0; i < 2; i++) {
                Serial.println("flash");
                LED_state = HIGH;
                digitalWrite(LED, LED_state);
                delay(80);
                LED_state = LOW;
                digitalWrite(LED, LED_state);
                delay(80);
            }
        }
    }

    delay(100);
}
