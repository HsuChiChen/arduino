/* 利用SPI進行2個Arduino板子之間通訊，2個Arduino板子都分別帶有1個LED和1個按鈕。
按下一端的按鈕，使另一端的LED亮起，放開後熄滅。*/
#include <SPI.h>
#define LED 7
#define buttonpin 2
volatile boolean received;
volatile byte Slavereceived, Slavesend;
;
int button;
int buttonvalue;
int x;
void setup() {
    Serial.begin(9600);
    SPCR |= bit(SPE);       //開啟從機的SPI通訊
    pinMode(MISO, OUTPUT);  //主入從出

    pinMode(buttonpin, INPUT);
    pinMode(LED, OUTPUT);
    received = false;

    SPI.attachInterrupt();  //啟用中斷函式
}

ISR(SPI_STC_vect) {        //SPI中斷程序
    Slavereceived = SPDR;  //從SPI Data Register獲取資料(byte)
    received = true;
}

void loop() {
    //Logic to SET LED ON OR OFF depending upon the value recerived from master
    if (received) {
        if (Slavereceived == 1) {
            digitalWrite(LED, HIGH);  //Sets pin 7 as HIGH LED ON
            Serial.println("Slave LED ON");
        } else {
            digitalWrite(LED, LOW);  //Sets pin 7 as LOW LED OFF
            Serial.println("Slave LED OFF");
        }

        buttonvalue = digitalRead(buttonpin);  // Reads the status of the pin 2

        //Logic to set the value of x to send to master
        if (buttonvalue == HIGH) {
            x = 1;

        } else {
            x = 0;
        }

        Slavesend = x;
        SPDR = Slavesend;  //Sends the x value to master via SPDR
        delay(1000);
    }
}