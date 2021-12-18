// 利用SPI進行2個Arduino板子之間通訊，傳送字串"Hello, world!"。
#include <SPI.h>
char buf[100];
volatile byte pos;
volatile bool flag;

void setup() {
    Serial.begin(9600);
    Serial.println();
    SPCR |= bit(SPE);       // turn on SPI in slave mode
    pinMode(MISO, OUTPUT);  //設定主入從出

    pos = 0;  // buffer empty
    flag = false;
    SPI.attachInterrupt();  // turn on interrupt
}

// SPI interrupt routine
ISR(SPI_STC_vect) {
    byte c = SPDR;  // read byte from SPI Data Register
    if (pos < sizeof(buf)) {
        buf[pos++] = c;              // save data in the next index in the array buff
        if (c == '\r') flag = true;  //check for the end of the word
    }
}

void loop() {
    if (flag) {
        flag = false;
        Serial.println(buf);
        pos = 0;
    }
}
