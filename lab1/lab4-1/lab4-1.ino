// 以模組Keypad鍵入資料，將資料傳輸至serial monitor。
const byte colPins[4] = {2, 3, 4, 5};             //行腳位(column)
const byte rowPins[4] = {A0, A1, A2, A3};         //列腳位(row)
const char keymap[4][4] = {{'1', '2', '3', 'A'},  //Keypad對應符號
                           {'4', '5', '6', 'B'},
                           {'7', '8', '9', 'C'},
                           {'*', '0', '#', 'D'}};

void setup() {
    Serial.begin(9600);
    Serial.println("Start:");
    for (int i = 0; i <= 3; i++) {
        pinMode(rowPins[i], INPUT_PULLUP);
        pinMode(colPins[i], OUTPUT);
        digitalWrite(colPins[i], HIGH);
    }
}

void loop() {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            digitalWrite(colPins[j], LOW);  //input 0 in each column

            //detect each row value
            if (digitalRead(rowPins[i]) == LOW) {
                Serial.println(keymap[i][j]);
                delay(200);  // to press button time
                digitalWrite(colPins[j], HIGH);
                break;
            } else
                digitalWrite(colPins[j], HIGH);
        }
    }
}
