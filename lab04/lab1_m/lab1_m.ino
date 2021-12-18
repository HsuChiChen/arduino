// 利用I2C進行Arduino間通訊。
#include <Wire.h>
#define SLAVE_ADDRESS 0x12 
#define SERIAL_BAUD 57600

void setup() {
    Wire.begin();
    Serial.begin(SERIAL_BAUD);
    Serial.println("I2C Master.02 started");
    Serial.println();
}

void loop() {
    if (Serial.available()) {
      Wire.beginTransmission(SLAVE_ADDRESS);
        while (Serial.available()) {
            Wire.write(Serial.read());
            delay(10);
        }
        Wire.endTransmission();
    }
}
