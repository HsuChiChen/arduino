// 利用keypad與LCD實現四則運算計算機。
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>  //LCD_12
#include <Wire.h>
//#include <ctype.h>
//#include <stdio.h>
//#include <stdlib.h>
#define MAX 100

//for LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);  //LCD
int lcd_row, lcd_col;                //i:lcd顯示位置,j:數字陣列位址
//for keypad
char key[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};
byte colPin[4] = {6, 7, 8, 9};
byte rowPin[4] = {2, 3, 4, 5};
Keypad keypad(makeKeymap(key), rowPin, colPin, 4, 4);

//global var
// char ifix[MAX] = "1+44";
char infix[MAX];
double answer;
int count;
char enter;

//subfuntion declaration
void IToPfix(char *ifix,
             char *pfix);    // Make infix expression into postfix with a stack
int priority(char);          // Set operators priority
double pfix_parser(char *);  // Use another stack to parse the postfix expression
double calculate(char, double, double);

void setup() {
    Serial.begin(9600);
    //for LCD
    lcd.init();       //LCD
    lcd.backlight();
    lcd.setCursor(0, 0);
}

void loop() {
    count = 0;
    while (true) {
        enter = keypad.getKey();
        if (enter != NO_KEY) {  //valid value
            infix[count] = enter;
            if (enter == '#') {
                infix[count] = '\0';
                break;
            } else if (enter == 'A') {
                infix[count] = '+';
            } else if (enter == 'B') {
                infix[count] = '-';
            } else if (enter == 'C') {
                infix[count] = '*';
            } else if (enter == 'D') {
                infix[count] = '/';
            }

            Serial.print(infix[count]);
            lcd.setCursor(count, 0);
            lcd.print(infix[count]);
            count++;
        }
    }

    answer = pfix_parser(infix);

    Serial.println();
    Serial.print('=');
    Serial.println(answer);
    lcd.setCursor(0, 1);
    lcd.print('=');
    lcd.setCursor(1, 1);
    lcd.print(answer);

    while (true) {
        enter = keypad.getKey();
        if (enter == '*') {
            lcd.clear();
            break;
        }
    }
}

void IToPfix(char *ifix, char *pfix) {
    char stack[MAX] = {'\0'};
    int i, j, top;
    for (i = 0, j = 0, top = 0; ifix[i] != '\0'; i++)
        switch (ifix[i]) {
            case '(':  // If meet ( then push it to stack
                stack[++top] = ifix[i];
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                while (priority(stack[top]) >=
                       priority(ifix[i])) {  // If meet an op then pop ops which
                                             // priority >= current op
                    pfix[j++] = stack[top--];
                }
                stack[++top] = ifix[i];
                break;
            case ')':
                while (stack[top] !=
                       '(') {  // If meet ) then pop all ele from stack until meet (
                    pfix[j++] = stack[top--];
                }
                top--;  // Dispose ) directly
                break;
            default:  // If meet a number then set a char n to locate the cut point
                      // of the number(So it support more then a single digits)
                while (isdigit(ifix[i]))
                    pfix[j++] = ifix[i++];
                pfix[j++] = 'n';
                i--;
        }
    while (top > 0) {
        pfix[j++] = stack[top--];
    }
}

int priority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

double pfix_parser(char *ifix) {
    char pfix[MAX] = {'\0'};
    double stack[MAX] = {0.0};

    IToPfix(ifix, pfix);

    int top, i;
    for (top = 0, i = 0; pfix[i] != '\0'; i++)
        switch (pfix[i]) {
            case '+':
            case '-':
            case '*':
            case '/':
                stack[top - 1] = calculate(pfix[i], stack[top - 1], stack[top]);
                top--;
                break;
            default:
                if (isdigit(pfix[i])) {
                    stack[++top] = atof(pfix + i);
                    while (pfix[i + 1] != 'n')
                        i++;
                }
        }

    return stack[top];
}

double calculate(char op, double a, double b) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
    }
    return 0;
}
