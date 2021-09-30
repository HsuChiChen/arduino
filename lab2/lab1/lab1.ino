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
byte colpin[4] = {7, 8, 9, 10};
byte rowpin[4] = {3, 4, 5, 6};
Keypad keypad(makeKeymap(key), rowpin, colpin, 4, 4);
void setup() {
    Serial.begin(9600);
    Serial.println("Enter the password :");
}

void loop() {
    count = 0;
    while (true) {  //4-digit number
        enter = keypad.getKey();
        if (enter != NO_KEY) {  //valid value
            value[count++] = enter;
            Serial.print(enter);
        }
        if (enter == 'A') break;
    }

    Serial.println();
    Serial.println();

    //if(strcmp(value, password) == 0){
    if (value[0] == password[0] && value[1] == password[1] && value[2] == password[2] && value[3] == password[3]) {  //hit the answer

        Serial.println("Unlock!");
    } else {
        Serial.println("Wrong passwords!");
        Serial.println("Try again");
    }
    delay(500);
}
