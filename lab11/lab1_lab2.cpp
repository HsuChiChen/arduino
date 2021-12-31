// 開發板連接滑鼠。
// - 在serial monitor上顯示滑鼠的資訊
// - 滑鼠控制LED燈 - 左鍵LED1閃爍、右鍵LED2閃爍、中鍵LED3閃爍
// 開發板連接鍵盤。
// - 在serial monitor上顯示使用者輸入字母或符號

#include "USBHostKeyboard.h"
#include "USBHostMouse.h"
#include "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

void onKey(uint8_t key) {
    printf("Key: %c\r\n", key);
}

void onMouseEvent(uint8_t buttons, int8_t x, int8_t y, int8_t z) {
    printf("buttons: %d, x: %d, y: %d, z: %d\r\n", buttons, x, y, z);

    if (buttons == 1) {
        led1 = 1;
        Thread::wait(200);
        led1 = 0;
    } else if (buttons == 2) {
        led2 = 1;
        Thread::wait(200);
        led2 = 0;
    } else if (buttons == 4) {
        led3 = 1;
        Thread::wait(200);
        led3 = 0;
    }
}

void keyboard_task(void const *) {
    USBHostKeyboard keyboard;

    while (1) {
        // try to connect a USB keyboard
        while (!keyboard.connect())
            Thread::wait(500);

        // when connected, attach handler called on keyboard event
        keyboard.attach(onKey);

        // wait until the keyboard is disconnected
        while (keyboard.connected())
            Thread::wait(500);
    }
}

void mouse_task(void const *) {
    USBHostMouse mouse;

    while (1) {
        // try to connect a USB mouse
        while (!mouse.connect())
            Thread::wait(500);

        // when connected, attach handler called on mouse event
        mouse.attachEvent(onMouseEvent);

        // wait until the mouse is disconnected
        while (mouse.connected())
            Thread::wait(500);
    }
}

int main() {
    Thread keyboardTask(keyboard_task, NULL, osPriorityNormal, 256 * 4);
    Thread mouseTask(mouse_task, NULL, osPriorityNormal, 256 * 4);
    while (1) {
        //led=!led;
        Thread::wait(500);
    }
}