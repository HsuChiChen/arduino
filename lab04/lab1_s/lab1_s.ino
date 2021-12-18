// 利用I2C進行Arduino間通訊。
#include <Wire.h>
#define SLAVE_ADDRESS 0x12
#define SERIAL_BAUD 57600

void receiveEvent();
void setup() {
    Wire.begin(SLAVE_ADDRESS);     //join 120 bus as a slave with address 1
    Wire.onReceive(receiveEvent);  // register event
    Serial.begin(SERIAL_BAUD);
    Serial.println();
    Serial.println("12C Slave.02 started\n");
}
void loop() {}

void receiveEvent(int howMany) {
    Serial.println("Receive Data:");
    while (Wire.available()) {
        Serial.print((char)Wire.read());
    }
    Serial.println("");
}
