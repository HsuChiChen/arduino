/* 承上題，增加2項功能 :
1. 修改密碼。
2. 添加驗證碼(透過七段顯示器顯示經過random()得出的3位驗證碼，
並在輸入錯誤時再隨機變換一組驗證碼直到輸入正確)。 */
#include <Key.h>
#include <Keypad.h>

#include "show_seg.h"

//declare function
void input(char terminal_char, char value[]);
void input_3(char terminal_char, char arr[]);

char password[] = "0000";
char value[5] = {0};
int count = 0;
char enter;
int verification;
char key[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};
byte colPin[4] = {13, 9, A4, A5};
byte rowPin[4] = {A0, A1, A2, A3};
Keypad keypad(makeKeymap(key), rowPin, colPin, 4, 4);
SHOW_SEG show_seg(2, 13);  //set pin2- pin13 as signal

void setup() {
    Serial.begin(9600);
    Serial.println();
    Serial.println();
    Serial.println("Wlcome to security box system");
    Serial.println("Enter your password press 'A' (press 'A' as enter)");
    Serial.println("Reset your password press 'B' (press '#' as enter)");
    Serial.println("----------------");
    Serial.println("----------------");
    randomSeed(analogRead(0));
}

void loop() {
    char enter = keypad.getKey();
    if (enter != NO_KEY) {
        if (enter == 'B') {
            Serial.println("Reset your password (press '#' as enter):");
            input('#', password);

            //check new password
            Serial.print("Sucess! New password is ");
            for (int i = 0; i < 4; i++)
                Serial.print(password[i]);
            Serial.println();
            Serial.println("----------------");
            Serial.println("----------------");
        } else if (enter == 'A') {
            Serial.println("Enter the password (press 'A' as enter):");
            input('A', value);
            //compare input and password
            if (strcmp(value, password) == 0) {
                Serial.println("Unlock!");
                Serial.println("----------------");
                Serial.println("----------------");

                //generate verifiation number
                while (true) {
                    verification = random(0, 999);
                    // Serial.print("verification : ");
                    // Serial.println(verification);
                    Serial.println("Enter 3-digit verification code (press 'A' as enter):");
                    input_3('A', value);
                    if (verification == atoi(value)) {
                        Serial.println("Correct!");
                        break;
                    } else {
                        Serial.println("Incorrect!");
                    }
                }

            } else {
                Serial.println("Wrong passwords!");
                Serial.println("Try again");
            }
            delay(500);
        }
    }
}

//enter 4-digit number and press "terminal_char" as enter
void input(char terminal_char, char arr[]) {
    count = 0;
    char enter = keypad.getKey();
    while (true) {
        enter = keypad.getKey();
        if (enter != NO_KEY) {  //valid value
            if (isDigit(enter)) {
                arr[count++] = enter;
                Serial.print(enter);
            } else if (enter == terminal_char) {
                Serial.println();
                break;
            }
        }
    }
}

//enter 3-digit number and press "terminal_char" as enter
void input_3(char terminal_char, char arr[]) {
    count = 0;
    char enter = keypad.getKey();
    while (true) {
        show_seg.show(verification);
        enter = keypad.getKey();
        if (enter != NO_KEY) {  //valid value
            arr[count++] = enter;
            if (isDigit(enter)) {
                Serial.print(enter);
            } else if (enter == terminal_char) {
                Serial.println();
                break;
            }
        }
    }
}