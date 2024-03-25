#include "Button.h"

Button::Button(int pin, bool input_pullup){
    this->pin = pin;
    if (input_pullup){
        pinMode(pin, INPUT_PULLUP);
    }else{
        pinMode(pin, INPUT);
    }
}

void Button::update(){
    state = digitalRead(this->pin);
    if (this->state && !this->last_state){
        this->clicks_time[this->clicks_index][0] = millis();
        this->position = "UP";
    }
    if (!this->state && this->last_state){
        this->clicks_time[this->clicks_index][1] = millis();
        this->position = "DOWN";
        if (this->clicks_index < this->max_values - 1){
            this->clicks_index++;
        }else{
            this->clicks_index = 0;
            this->reset = true;
        }
    }
}

String Button::get(){

    // vzdycky musim jit od index pozpatku a kdyz narazim ze nejaky uz se nepocita jako klik, tka nepokracovat a return 
    // udelat funkci, ktera mi vrati jenom hodnoty serazeny s kteryma budu pracovat + kolik jich je (z kterych budu zjistovat jestli jsou po sobe vubec)
}

String Button::get_position(){
    return this->position;
}