// 不使用`analogRead()`，讀取可變電阻之類比值，並在Serial port顯示出來。
// 使用ADMUX、ADCSRA及ADCH/L Register。
int x = A1;
void setup() {
    Serial.begin(115200);

    ADMUX |= (1 << REFS0);                                 // TODO: set voltage reference as AVCC
    ADCSRA |= (1 << ADEN);                                 // TODO: enable ADC
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // TODO: prescale
}

uint16_t ReadADC(byte pin) {
    ADMUX |= (1 << MUX0);             // TODO: set channel
    ADCSRA |= (1 << ADSC);            // TODO: start conversion
    while (bit_is_set(ADCSRA, ADSC))  // TODO: wait until conversion complete
        return ADC;  // TODO: return data
}

void loop() {
    Serial.println(ReadADC(x));  // x means number of analog in pin
}
