#include <Keypad.h>
#include <LiquidCrystal_I2C.h>  //LCD_12
#include <Wire.h>

//---------------for lcd-----------------//
LiquidCrystal_I2C lcd(0x27, 16, 2);  //LCD
float number[2];
float answer;
char operation;
//int lcd_row = 0;
//int lcd_col = 0;
int count_num = 0;
//---------------for lcd-----------------//

//--------------for keypad-------------//
char key[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};
byte colPin[4] = {6, 7, 8, 9};
byte rowPin[4] = {2, 3, 4, 5};
//--------------for keypad-------------//

Keypad mykeypad(makeKeymap(key), rowPin, colPin, 4, 4);

void setup() {
    lcd.clear(); //reset LCD
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    //lcd.print("NCKU");
}

void loop() {
    //lcd.print(int(number[0]));
    //lcd.print(int(number[1]));
    
    //透過Keypad函式庫裡的getkey()方法讀取按鍵的字元
    int key = mykeypad.getKey();
    if (key != NO_KEY) {
        //若有按鍵按下則顯示按下的字元
        delay(100);
        switch (key) {
            case 'A':
                //Add();
                operation = '+';
                lcd.print(operation);
                break;
            case 'B':
                //Subtract();
                operation = '-';
                lcd.print(operation);
                break;
            case 'C':
                //Multiply();
                operation = '*';
                lcd.print(operation);
                break;
            case 'D':
                //Divide();
                operation = '/';
                lcd.print(operation);
                break;
            case '#':
                Equal();
                lcd.setCursor(0, 1);
                lcd.print('=');
                break;
            case '*':
                Clear();
                break;
            default:
                Getnumber(key);
        }
    }
}
void Getnumber(int key) {
  int digit = key -48; // char to int
  
  if(operation && count_num == 0) count_num++;
  number[count_num] = number[count_num]*10 + digit;
  lcd.print(digit); //print number
}
void Equal(){
  switch(operation){
    case '+':
      answer = number[0] + number[1];
      break;
    case '-':
      answer = number[0] - number[1];
      break;
    case '*':
      answer = number[0] * number[1];
      break;
    case '/':
      answer = number[0] / number[1];
      break;
  }
  lcd.setCursor(1, 1);
  lcd.print(answer); //print answer
}
void Clear(){
  lcd.clear(); //reset LCD
  number[0] = 0;
  number[1] = 0;
  operation = '\0';
  answer = 0;
  count_num = 0;
}
