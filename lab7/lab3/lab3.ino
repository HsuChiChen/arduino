// 不使用`delay()`，使用超聲波模組，每秒測量一次距離，並顯示在多工七段顯示器上。
//---------------for 7-segment---------------//
const int SEG_COM[4] = {10, 11, 12, 13};  //控制線
const int SEG_data[10][7] = {
    {1, 1, 1, 1, 1, 1, 0},   //"0"  //資料線
    {0, 1, 1, 0, 0, 0, 0},   //"1"
    {1, 1, 0, 1, 1, 0, 1},   //"2"
    {1, 1, 1, 1, 0, 0, 1},   //"3"
    {0, 1, 1, 0, 0, 1, 1},   //"4"
    {1, 0, 1, 1, 0, 1, 1},   //"5"
    {1, 0, 1, 1, 1, 1, 1},   //"6"
    {1, 1, 1, 0, 0, 0, 0},   //"7"
    {1, 1, 1, 1, 1, 1, 1},   //"8"
    {1, 1, 1, 0, 0, 1, 1}};  //"9"
int disp[4];                 //顯示數字
int number = 0;
int set = 0;
int temp;
int trigPin = A0;  //Trig Pin
int echoPin = A1;  //Echo Pin
long duration, cm;

void setup() {
    Serial.begin(115200);
    DDRB = (1 << 5);  // set pin 13 as output mode by DDR?
    // set 超音波
    pinMode(trigPin, OUTPUT);  // 定義輸入及輸出
    pinMode(echoPin, INPUT);

    //set 七段
    //set 7-segment 3digit
    for (int i = 2; i <= 12; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, HIGH);
    }

    noInterrupts();         // disable interrupts
    TCCR1A = 0;             // TCCR1A Reset
    TCCR1B = 0;             // TCCR1B Reset
    TCCR1B |= (1 << CS12);  // 256 prescaler

    TCCR1B |= (1 << WGM12);   // set CTC mode by TCCR1?
    TIMSK1 |= (1 << OCIE1A);  // enable Timer1 compare match interrupt by TIMSK?
    TCNT1 = 0;                // reset Timer1 by TCNT1

    OCR1A = 62500;  // set compare value by OCR1?
    interrupts();   // enable interrupts
}

// interrupt
ISR(TIMER1_COMPA_vect) {
    noInterrupts();
    PORTB ^= (1 << 5);  // blink
    supersonic();
    interrupts();
}

void loop() {
    show_digit();
}

void supersonic() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);  // 給 Trig 高電位，持續 10微秒
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    pinMode(echoPin, INPUT);            // 讀取 echo 的電位
    duration = pulseIn(echoPin, HIGH);  // 收到高電位時的時間

    cm = (duration / 2) / 29.1;  // 將時間換算成距離 cm 或 inch

    Serial.print("Distance : ");
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
}

void show_digit() {
    number_transfer(cm);
    for (int i = 0; i < 4; i++) {
        digitalWrite(SEG_COM[i], LOW);
        SEG_Drive(disp[i]);
        delay(5);
        digitalWrite(SEG_COM[i], HIGH);
    }
}
void number_transfer(int Num) {  //三位數拆成三個獨立的數字，存入陣列disp[]中
    int temp = Num;
    for (int i = 0; i < 4; i++) {
        disp[i] = temp % 10;  //取餘數
        temp = temp / 10;
    }
}
void SEG_Drive(int number) {  //將字元變數從SEG_data[][]找到相對應的位置，並寫入a~g中
    for (int i = 2; i < 9; i++)
        digitalWrite(i, SEG_data[number][i - 2]);
}
