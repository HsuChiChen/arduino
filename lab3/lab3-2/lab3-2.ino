// 手機終端機輸入再透過藍芽傳資料，實現密碼鎖功能。
#include <SoftwareSerial.h>

#include "show_seg.h"
SoftwareSerial BTSerial(10, 11);  // 宣告10腳位為Arduino的RX 、11為Arduino的 TX
SHOW_SEG show_seg(2, 9, A0, A3);  //set pin2- pin13 as signal

char val;
char password[5] = {0};
char input[5] = {0};
int error = 0;
bool reset_mode = false;
unsigned long timer = 0;
int ten_second = 10;

void setup() {
    Serial.begin(9600);
    Serial.println();
    BTSerial.begin(38400);  //注意，HC-05要設定成38400
    Serial.println("Start :");
}
void loop() {
    // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
    if (BTSerial.available()) {
        val = BTSerial.read();
        //        Serial.print(val);
    }

    //press 'B' to enter reset password mode
    if (val == 'B') {
        reset_mode = true;
        Serial.println();
        Serial.println("\"reset password\" mode");
    }

    int count = 0;
    while (reset_mode) {
        if (BTSerial.available()) {
            // 讀取傳入的字元值
            while ((val = BTSerial.read()) != '\n') {
                // 確認字元值不等於-1，而且索引i小於4（確保僅讀取前4個字）
                if (val != -1 && count < 4 && val != '\r') {
                    password[count++] = val;
                }
            }
        }

        while (count == 4) {
            reset_mode = false;  //quit reset mode
            Serial.print("Success! New password is : ");
            for (int i = 0; i < 4; i++) {
                Serial.print(password[i]);
            }
            Serial.println();
            count = 0;
        }
    }

    //enter password
    while (isDigit(val) && count < 4) {
        input[count++] = val;
        if (BTSerial.available()) {
            // 讀取傳入的字元值
            while ((val = BTSerial.read()) != '\n') {
                // 確認字元值不等於-1，而且索引i小於4（確保僅讀取前4個字）
                if (val != -1 && count < 4) {
                    input[count++] = val;
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            Serial.print(input[i]);
        }
        Serial.println();
        //compare input and password
        if (strcmp(input, password) == 0) {
            Serial.println("----------------");
            Serial.println("Unlock!");
            Serial.println("----------------");
        } else {
            Serial.println("Wrong passwords!");
            Serial.println("Try again");
            Serial.print("Number of error : ");
            Serial.println(error + 1);
            error++;
        }
    }
    show_seg.show(error);
    if (error == 3) {
        Serial.println("wait for 10 sec");
        timer = millis();
        Serial.println(ten_second);
    }

    while (error == 3) {
        show_seg.show(ten_second);
        //clear bluetooth HC-05 buffer
        if (BTSerial.available()) {
            BTSerial.read();
        }

        //minus number with 1 sec
        if (millis() - timer > 1000) {
            ten_second--;
            Serial.println(ten_second);
            timer = millis();
            if (ten_second == 0) {
                Serial.println("time out!");
                ten_second = 10;
                error = 0;  //reset error to 0 and quit if loop
            }
        }
    }
}
