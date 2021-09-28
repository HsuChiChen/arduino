const int button = 2;
const int led = 13;      //UNO內建LED
const int tick_led = 8;  //每秒亮暗的led
bool led_state = HIGH;
bool tick_led_state = HIGH;

int now = 0;   //每秒+1
int same = 0;  //紀錄狀態維持
int debounce_threshold = 200;

void setup() {
    pinMode(button, INPUT_PULLUP);  //上拉
    pinMode(led, OUTPUT);
    digitalWrite(led, led_state);
    pinMode(tick_led, OUTPUT);
    digitalWrite(tick_led, tick_led_state);
}

void loop() {
    if (digitalRead(button) == HIGH)  //沒按按鈕
        same = 0;
    else if (digitalRead(button) != HIGH) {  //按按鈕
        same++;
        if (same == debounce_threshold) {  //debounce
            led_state = !led_state;
            digitalWrite(led, led_state);
        }
    }
    if (((millis() / 1000) - now) != 0) {  //判斷過了一秒
        now++;
        tick_led_state = !tick_led_state;  //改變亮暗
        digitalWrite(tick_led, tick_led_state);
    }
}
