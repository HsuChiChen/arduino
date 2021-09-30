/*自訂一個密碼，使用Keypad來輸入值，
輸入完成後按Ａ送出，
若輸入值與密碼相同則印出Unlock!，錯誤則印出Wrong passwords!。*/
#include <Key.h>
#include <Keypad.h>

char password[] = "1234";
char value[5] = {0};
int count = 0;
char enter;
char key[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};
byte colPin[4] = {13, 9, A4, A5};
byte rowPin[4] = {A0, A1, A2, A3};
Keypad keypad(makeKeymap(key), rowPin, colPin, 4, 4);
void setup() {
    Serial.begin(9600);
    Serial.println();
    Serial.println("Enter the password :");
}

void loop() {
    count = 0;
    while (true) {  //4-digit number
        enter = keypad.getKey();
        if (enter != NO_KEY) {  //valid value
            if (enter == 'A') {
                break;
            } else {
                value[count++] = enter;
                Serial.print(enter);
            }
        }
    }

    Serial.println();
    Serial.println();

    if (strcmp(value, password) == 0) {
        Serial.println("Unlock!");
    } else {
        Serial.println("Wrong passwords!");
        Serial.println("Try again");
    }
    delay(500);
}
