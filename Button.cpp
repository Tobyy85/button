#include "Button.h"

Button::Button(int pin, bool input_pullup, int long_click_time, int multiple_click_time){
  this->pin = pin;
  this->input_pullup = input_pullup;
  this->long_click_time = long_click_time;
  this->multiple_click_time = multiple_click_time;
  if (input_pullup){
    pinMode(pin, INPUT_PULLUP);
  }else{
    pinMode(pin, INPUT);
  }
}


bool Button::get_state(){
  if (this->input_pullup){
    return digitalRead(this->pin) == LOW;
  }else{
    return digitalRead(this->pin) == HIGH;
  }
}

bool Button::pressed_down(){
  return this->state && !this->last_state;
}

bool Button::pressed_up(){
  return !this->state && this->last_state;
}

void Button::update(){
    this->last_state = this->state;
    this->state = this->get_state();

    if (this->pressed_down()){
      this->last_click_down_millis = this->click_down_millis;
      this->click_down_millis = millis();
        if (click_down_millis - last_click_up_millis <= this->multiple_click_time){
          this->count++;
        }
        else{
          this->count = 1;
        }
      this->changed = true;
    }

    if (this->pressed_up()){
      this->last_click_up_millis = this->click_up_millis;
      this->click_up_millis = millis();
    }
}

int Button::get(bool update){  
  if (update){
    this->update();
  }
  if (millis() - this->click_down_millis > this->multiple_click_time && this->changed){
    this->changed = false;
    return this->count;
  }else{
    return 0;
  }
}