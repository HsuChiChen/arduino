// 利用SPI進行2個Arduino板子之間通訊，傳送字串"Hello, world!"。
#include <SPI.h>

void setup() {
    digitalWrite(SS, HIGH);
    Serial.begin(9600);
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV8);  //set clock
}

void loop() {
    char c;
    digitalWrite(SS, LOW);  //enable SPI

    for (const char* p = "Hello, world!\r"; c = *p; p++) {
        SPI.transfer(c);
        Serial.println(c);
        //delay(500);
    }

    digitalWrite(SS, HIGH);  //disable SPI
    delay(5000);
}
