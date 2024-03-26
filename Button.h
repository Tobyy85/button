// TODO udelat to tak ze bude array ktera bude unsigned long[100][2] napr a budu tam zapisovat casy kdyz sly dolu a kdy nahoru (up down) a podle toho budu posuzovat co to bylo za klik 
#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"

class Button{
    public:
        Button(int pin);
        void update();
        String get_position();
        long** get_sorted_values(unsigned long time_arr[][2], int current_index);
        String get();

    private:
        int pin;
        int state;
        int last_state;
        int clicks_index = 0;
        String position = "UP";
        int long_click = 500;
        int double_click = 250;
        bool reset = false; 
        


        static const int max_values = 3;
        unsigned long clicks_time[max_values][2] = {};
        String clicks_names[4] = {"NO CLICK", "SINGLE CLICK", "DOUBLE CLICK", "TRIPLE CLICK"};

};



#endif