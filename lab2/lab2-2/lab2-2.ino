// 使用keypad輸入一個三位數字，實現終極密碼 answer ∈ [0,999]。
#include <Key.h>
#include <Keypad.h>

char guess_ch[5] = {0};
int guess, ans, upper, lower;

int count = 0;
char enter;
char key[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};
byte col_pin[4] = {13, 9, A4, A5};
byte row_pin[4] = {A0, A1, A2, A3};
Keypad keypad(makeKeymap(key), row_pin, col_pin, 4, 4);

void setup() {
    Serial.begin(9600);
    Serial.println();
    randomSeed(analogRead(0));  //time seed
}

void loop() {
    //initialization

    ans = random(0, 999);  //ans
    upper = 9999;
    lower = 0;

    //game start
    Serial.println("Game Start!!");
    Serial.println("guess the number with [0, 999]");
    Serial.println("press 'A' to enter");
    Serial.println(ans);  //ans

    while (true) {
        //store input value into "guess" array
        count = 0;
        while (true) {  //4-digit number
            enter = keypad.getKey();
            if (enter != NO_KEY) {  //input
                guess_ch[count++] = enter;
                if (isDigit(enter)) {
                    Serial.print(enter);
                } else if (enter == 'A') {
                    break;
                }
            }
        }
        Serial.println();
        guess = atoi(guess_ch);  //用最後的字符'A'判斷中止位數
        Serial.print(guess);

        if (guess > upper || guess < lower) {
            Serial.println(" => Out of bounding");
        }  //guess > ans
        else if (guess > ans) {
            upper = guess;
        }  //guess < ans
        else if (guess < ans) {
            lower = guess;
        }  ////hit the answer
        else if (guess == ans) {
            Serial.println(" => BINGO");
            Serial.println("----------------");
            Serial.println("----------------");
            Serial.println("----------------");
            Serial.println("----------------");
            delay(500);
            break;
        }

        Serial.print(" => ");
        Serial.print(lower);
        Serial.print(" ~ ");
        Serial.println(upper);
        Serial.println("----------------");
    }
}
