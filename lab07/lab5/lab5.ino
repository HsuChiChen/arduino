// 不使用`analogRead()`, `analogWrite()`。
// 藉由Timer1 Register中PWM模式，使用可變電阻調整LED之亮暗。
int x = A1;
const unsigned int TOP = 0x07FF;

void setup() {
    Serial.begin(115200);

    ADMUX |= (1 << REFS0);                                 // TODO: set voltage reference as AVCC
    ADCSRA |= (1 << ADEN);                                 // TODO: enable ADC
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // TODO: prescale

    TCCR1A = 0;  // TCCR1A Reset
    TCCR1B = 0;  // TCCR1B Reset
    OCR1A = 0;
    OCR1B = 0;

    // TODO: set to Timer1 to Waveform Generation Mode 14: Fast PWM with TOP set by ICR1
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << WGM13);

    OCR1B = constrain(0, 0, TOP);

    // TODO: set time prescale
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    // TODO: set clock prescale by TCCR?B
    TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS11);

    // TODO: set TOP by ICR1
    ICR1 = TOP;

    // TODO: enable fast PWM on pin: set OC1B at BOTTOM and clear OC1B on OCR1B compare by TCCR1A
    TCCR1A |= (1 << COM1B1);
    pinMode(10, OUTPUT);

    // TODO: set pinMode output
    DDRB |= (1 << PB2);  // pin9 output
}

uint16_t ReadADC(byte pin) {
    ADMUX |= (1 << MUX0);   // TODO: set channel
    ADCSRA |= (1 << ADSC);  // TODO: start conversion
    // TODO: wait until conversion complete
    while (bit_is_set(ADCSRA, ADSC))
        return ADC;  // TODO: return data
}

void loop() {
    Serial.println(ReadADC(x));
    OCR1B = constrain(ReadADC(1), 0, TOP);
    // TODO: write analog value by OCR?
}
