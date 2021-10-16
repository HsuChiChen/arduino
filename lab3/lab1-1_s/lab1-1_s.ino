// 利用SPI進行2個Arduino板子之間通訊，傳送字串"Hello, world!"。
#include <SPI.h>
char buf[100];
volatile byte pos;
volatile bool flag;

void setup() {
    Serial.begin(9600);
    Serial.println();
    SPCR |= bit(SPE);       //開啟從機的SPI通訊(SPCR |= (1<<SPE))
    pinMode(MISO, OUTPUT);  //設定主入從出

    pos = 0;  //buffer裡頭為空
    flag = false;
    SPI.attachInterrupt();  //啟用中斷函式
}

ISR(SPI_STC_vect) {
    byte c = SPDR;
    if (pos < sizeof(buf)) {
        buf[pos++] = c;
        if (c == '\r') flag = true;
    }
}

void loop() {
    if (flag) {
        flag = false;
        Serial.println(buf);
        pos = 0;
    }
}
