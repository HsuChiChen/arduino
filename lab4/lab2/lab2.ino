#include <LiquidCrystal_I2C.h>  //LCD_12
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  //LCD
int row = 0;
int len = 0;
void setup() {
    lcd.init();
    lcd.backlight();
}

void loop() {
    lcd.clear();
    lcd.setCursor(0, row);
    char name[] = "F94089032";
    Serial.begin(9600);
    len = strlen(name);
    Serial.println(strlen(name));

    //往右移一格顯示
    lcd.print(name);
    for (int i = 0; i < 16 - len; i++) {
        lcd.scrollDisplayRight();
        delay(500);
    }

    // 如果目前行數是0行，將Row + 1，往下跳一行
    if (row == 0) {
        row = row + 1;
        lcd.clear();
        lcd.setCursor(16 - len, 1);
        lcd.print(name);
        delay(500);
    }

    //往左移一格顯示
    for (int i = 0; i < 16 - len; i++) {
        lcd.scrollDisplayLeft();
        delay(500);
    }
    // 判斷目前行數, 是1行，將Row 改為0行
    if (row == 1) {
        row = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(name);
        delay(500);
    }
}
