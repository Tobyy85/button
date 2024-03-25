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

}


String Button::get_position(){
    return this->position;
}