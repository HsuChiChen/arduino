/* 利用SPI進行2個Arduino板子之間通訊，2個Arduino板子都分別帶有1個LED和1個按鈕。
按下一端的按鈕，使另一端的LED亮起，放開後熄滅。*/
#include <SPI.h>
#define LED 7
#define buttonpin 2
int button;
int x;

void setup(void) {
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV8);  //設定時脈為 16/8 = 2 Mhz
    digitalWrite(SS, HIGH);               // 確保ss初始狀態為high

    //Serial.begin(9600);
    pinMode(buttonpin, INPUT);
    pinMode(LED, OUTPUT);
}

void loop(void) {
    // read button state
    bool master_button = digitalRead(buttonpin);
    if (master_button == HIGH) {
        x = 1;
    } else {
        x = 0;
    }

    //tansfer or receive data to slave
    byte Master_send, Master_receive;
    digitalWrite(SS, LOW);
    Master_send = x;
    Master_receive = SPI.transfer(Master_send);  //send MOSI, receive MISO
    //Master_receive = SPI.transfer(0);
    //Serial.println(x); // use for test

    if (Master_receive == 1) {
        digitalWrite(LED, HIGH);
        //Serial.println("Master LED on");
    } else {
        digitalWrite(LED, LOW);
        //Serial.println("Master LED off");
    }

    digitalWrite(SS, HIGH);
    delay(1000);
}
