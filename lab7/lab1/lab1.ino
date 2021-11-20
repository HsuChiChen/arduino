// 不使用`delay()`達成每2秒改變LED亮或暗。
// 使用Timer1 Register、Output Compare A Match Interrupt中斷模式、CTC mode。
void setup() {
    Serial.begin(115200);
    DDRB = (1 << 5);  // set pin 13 as output mode by DDR?

    noInterrupts();                       // disable interrupts
    TCCR1A = 0;                           // TCCR1A Reset
    TCCR1B = 0;                           // TCCR1B Reset
    TCCR1B |= (1 << CS12) | (1 << CS10);  // 1024 prescaler

    TCCR1B |= (1 << WGM12);   // set CTC mode by TCCR1?
    TIMSK1 |= (1 << OCIE1A);  // enable Timer1 compare match interrupt by TIMSK?
    TCNT1 = 0;                // reset Timer1 by TCNT1

    OCR1A = 31250;  // set compare value by OCR1?
    interrupts();   // enable interrupts
}

// interrupt
ISR(TIMER1_COMPA_vect) {
    noInterrupts();
    PORTB ^= (1 << 5);  // blink
    interrupts();
}

void loop() {
    Serial.println(TCNT1);
}
