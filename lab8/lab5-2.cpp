// 實現呼吸燈。亮暗週期為亮至暗2秒、暗至亮2秒。
#include "mbed.h"
#define NORMAL (65536 / 2000)

int main() {
    AnalogOut led1(PA_4);       //0~65536
    unsigned short sample = 0;  // write to A5 pin

    Timer timer;
    int t_ms;
    timer.start();

    while (1) {
        t_ms = timer.read_ms();
        led1.write_u16(sample);  //analog write
        //前2秒漸亮；後2秒漸暗
        sample = (t_ms % 4000 < 2000) ?  NORMAL * (t_ms % 2000) : NORMAL * (2 - (t_ms % 2000));
    }
}