// 使用Timer，消除USER_BUTTON的去彈跳現象，然後記錄BUTTON被按下的次數，
// 在USER_BUTTON被按下時輸出次數到serial monitor。
#include "mbed.h"

int main() {
    int count = 0;
    // button setting
    DigitalIn button(USER_BUTTON);  //the button on your board
    if (button.is_connected())
        printf("\rbutton is connected and initialized!\n\r");
    button.mode(PullNone);  //浮接

    // timer setting
    Timer timer;
    int t_ms;
    timer.start();

    while (1) {
        t_ms = timer.read_ms();

        //after 400ms
        if (button.read() && (t_ms > 400)) {
            while (1) {
                // release button
                if (!button.read()) {
                    count++;
                    printf("%d\n\r", count);
                    timer.reset();  // counting from 0
                    break;
                }
            }
        }
    }
}