#include <Keypad.h>  //引用Keypad函式庫
#define KEY_ROWS 4   //按鍵模組的列數
#define KEY_COLS 4   //按鍵模組的行數

byte colPins[4] = {2, 3, 4, 5};
byte rowPins[4] = {A0, A1, A2, A3};
char keymap[KEY_ROWS][KEY_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
Keypad myKeypad(makeKeymap(keymap), rowPins, colPins, KEY_ROWS, KEY_COLS);

char buffer[1000];
int count = 0;  //指向存到第幾位數的指針

void setup() {
    Serial.begin(9600);
}

void loop() {
    //透過Keypad函式庫裡的getkey()方法讀取按鍵的字元
    char key = myKeypad.getKey();
    
    //若有按鍵按下則顯示按下的字元
    if (key) {
        Serial.println(key);
        buffer[count] = key;
        count++;

        //print serise of char
        if (key == '#') {
            for (int i = 0; i < count - 1; i++) {
                Serial.print(buffer[i]);
            }
            Serial.println();
            count = 0;
        }
    }
}
