/* 承上題，增加2項功能 :
1. 修改密碼。
2. 添加驗證碼(透過七段顯示器顯示經過random()得出的3位驗證碼，
並在輸入錯誤時再隨機變換一組驗證碼直到輸入正確)。 */
#include <Key.h>
#include <Keypad.h>
#include <Password.h>

#include "show_seg.h"
int KeyNumber(char keyA);
bool True_OR_false();
void Generate_verification();

Password password = Password("1234");
SHOW_SEG show_seg(2, 13);  //pin2- pin13 signal
String newPassword;

bool check = 0;
char buf[10] = "";
int buf_size = 0;
int verification;
char key[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};
byte colPin[4] = {13, 9, A4, A5};
byte rowPin[4] = {A0, A1, A2, A3};
Keypad keypad = Keypad(makeKeymap(key), rowPin, colPin, 4, 4);

//---------------for 7-segment---------------//
const int SEG_COM[3] = {11, 12, 13};  //控制線
const int SEG_data[10][7] = {
    {1, 1, 1, 1, 1, 1, 0},   //"0"  //資料線
    {0, 1, 1, 0, 0, 0, 0},   //"1"
    {1, 1, 0, 1, 1, 0, 1},   //"2"
    {1, 1, 1, 1, 0, 0, 1},   //"3"
    {0, 1, 1, 0, 0, 1, 1},   //"4"
    {1, 0, 1, 1, 0, 1, 1},   //"5"
    {1, 0, 1, 1, 1, 1, 1},   //"6"
    {1, 1, 1, 0, 0, 0, 0},   //"7"
    {1, 1, 1, 1, 1, 1, 1},   //"8"
    {1, 1, 1, 0, 0, 1, 1}};  //"9"
int disp[3];                 //顯示數字
void setup() {
    // put your setup code here, to run once: Serial.begin(9600);
    Serial.begin(9600);
    Serial.println();
    Serial.println("Enter password:");
    randomSeed(analogRead(0));
}
void loop() {  // put your main code here, to run repeatedly:
    char keyA = keypad.getKey();
    if (keyA != NO_KEY) {
        if (keyA == 'A') {
            True_OR_false();
            if (check) {
                check = 0;
                while (true) {
                    int count = 0;
                    int number = 0;  // verification you type
                    Generate_verification();
                    show_seg.show(verification);
                    while (true) {
                        char veri = keypad.getKey();
                        show_seg.show(verification);
                        if (veri != NO_KEY) {
                            Serial.print(veri);
                            number = number * 10 + int(veri) - 48;
                            count++;
                            if (count == 3) {
                                count = 0;
                                break;
                            }
                        }
                    }
                    if (verification == number) {
                        Serial.println("\n驗證碼正確");
                        break;
                    } else {
                        Serial.println("\n驗證碼錯誤!");
                        Serial.println("請重新輸入驗證碼");
                    }
                }
                password.reset();  //驗證碼
            }
        } else if (keyA == 'B') {
            buf_size = 0;
            Serial.print("請設定新密碼:");
            while (true) {
                char key_B = keypad.getKey();
                if (key_B != NO_KEY) {
                    buf_size++;
                    if (key_B == '#') {
                        newPassword.toCharArray(buf, buf_size);
                        password.set(buf);
                        Serial.print("\nSuccess! Newpassword is ");
                        Serial.println(newPassword);
                        break;
                    } else {
                        Serial.print(key_B);
                        newPassword += key_B;
                    }
                }
            }
        } else
            KeyNumber(keyA);
    }
}

int KeyNumber(char keyA) {
    Serial.print(keyA);
    password.append(keyA);
}

bool True_OR_false() {
    Serial.println();
    if (password.evaluate()) {
        Serial.println("Unlock!");
        check = 1;
    } else {
        Serial.println(
            "Wrong passwords!\n"
            "請重新輸入密碼");
        check = 0;
    }
    return check;
}

void Generate_verification() {
    verification = random(999);
    //Serial.print("驗證碼：");
    //Serial.println(verification);
    delay(10);
}
