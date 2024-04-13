#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"

class Button{
    public:
        Button(int pin, bool input_pullup = true, int multiple_click_time = 400); // int multiple_click_time = 300
        bool get_state();
        void update();
        int get(bool update = true);

    private:
        bool pressed_down();
        int pin;
        bool input_pullup;
        int multiple_click_time;

        bool last_state = false;
        bool state = false;
        int count = 0;
        unsigned long last_click_millis = 0;
        unsigned long click_millis = 0;
        bool changed = false;

};

#endif