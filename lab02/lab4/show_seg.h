#ifndef SHOW_SEG_H
#define SHOW_SEG_H
#include <Arduino.h>
class SHOW_SEG {
   private:
    int first_pin;
    int last_pin;
    int display[4];

   public:
    SHOW_SEG(int first_pin, int last_pin);
    void init();
    void show(int num);
    void number_transfer(int num);
    void show_digit();
    void SEG_Drive(int num);
};
#endif