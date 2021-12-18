// 利用RTOS中的`Mail`與使用`Thread::wait()`計時實現碼錶。
// |Serial monitor輸入值|功能|
// |:-:|:-|
// |`'s'`|開始計時(精度: 10ms)|
// |`'p'`|顯示計時的秒數並停止計時|
// |`'r'`|歸零並停止計時|

#include "mbed.h"
#include "rtos.h"

Serial pc(SERIAL_TX, SERIAL_RX);
// Mail
typedef struct {
    bool clock_start;
    float counter; //counter value
} mail_t;

Mail<mail_t, 16> mail_box;

void send_thread(void) {
    float i = 0;
    char cmd;

    while (true) {
        mail_t *mail = mail_box.alloc();
        if (!(mail->clock_start)) i++;  // fake data update
        mail->counter = i / 1000;
        mail_box.put(mail);
        Thread::wait(1);

        if (pc.readable()) {
            cmd = pc.getc();
            pc.putc(cmd);
            pc.printf("\r\n");
            switch (cmd) {
                case 's':
                    printf("clock start now.....\n\r");
                    mail->clock_start = false;
                    break;
                case 'p':
                    printf("time = : %f\n\r", mail->counter);
                    mail->clock_start = true;
                    break;
                case 'r':
                    printf("reset time.....\n\r");
                    i = 0;
                    mail->clock_start = true;
                    break;
            }
        }
    }
}

int main(void) {
    Thread thread;
    thread.start(callback(send_thread));

    while (true) {
        osEvent evt = mail_box.get();
        if (evt.status == osEventMail) {
            mail_t *mail = (mail_t *)evt.value.p;

            //printf("Number of cycles: %u\n\r", mail->counter);

            mail_box.free(mail);
        }
    }
}
