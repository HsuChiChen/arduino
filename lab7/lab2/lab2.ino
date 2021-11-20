// 不使用`delay()`，顯示精度到毫秒的計時器在LCD螢幕上。
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  //LCD SDA->A4, SCL->A5
int ms = 0;
int s = 0;

void setup() {
    Serial.begin(115200);
    DDRB = (1 << 5);  // set pin 13 as output mode by DDR?
    lcd.init();
    lcd.backlight();
    lcd.clear();

    noInterrupts();                       // disable interrupts
    TCCR1A = 0;                           // TCCR1A Reset
    TCCR1B = 0;                           // TCCR1B Reset
    TCCR1B |= (1 << CS12) | (1 << CS10);  // 1024 prescaler

    TCCR1B |= (1 << WGM12);   // set CTC mode by TCCR1?
    TIMSK1 |= (1 << OCIE1A);  // enable Timer1 compare match interrupt by TIMSK?
    TCNT1 = 0;                // reset Timer1 by TCNT1

    OCR1A = 15.625;  // set compare value by OCR1?
    interrupts();    // enable interrupts
}

// interrupt
ISR(TIMER1_COMPA_vect) {
    noInterrupts();
    PORTB ^= (1 << 5);  // blink
    ms++;
    if (ms == 1000) {
        s++;
        ms = 0;
    }
    interrupts();
}

void loop() {
    Serial.println(TCNT1);
    lcd.setCursor(0, 0);
    lcd.print(s);  // second
    lcd.print(":");
    lcd.print(ms);  //micor second
}