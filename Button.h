#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"

class Button{
    public:
        Button(int pin);
        String get_position();
        String get();

    private:
        void update();
        long** get_sorted_values(unsigned long time_arr[][2], int current_index);
        bool is_press_and_hold(long** sorted_values);
        bool is_long_click(long** sorted_values);
        bool is_single_click(long** sorted_values);
        bool is_double_click(long** sorted_values);
        bool is_triple_click(long** sorted_values);

        int pin;
        int state;
        int last_state;
        int clicks_index = 0;
        String position = "UP";
        int long_click = 400;
        int multiple_click = 300;
        bool returned = true;
        
        static const int max_values = 3;
        unsigned long clicks_time[max_values][2] = {};
};

#endif