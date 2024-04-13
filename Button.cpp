#include "Button.h"

Button::Button(int pin, bool input_pullup, int multiple_click_time){
  this->pin = pin;
  this->input_pullup = input_pullup;
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

void Button::update(){
  this->state = this->get_state();
  if (pressed_down()){
    this->last_click_millis = this->click_millis;
    this->click_millis = millis();
    if (this->click_millis - this->last_click_millis <= this->multiple_click_time){
      this->count++;
    }else{
      this->count = 1;
    }
    this->changed = true;
  }
  this->last_state = this->state;
}

int Button::get(bool update){
  if (update){
    this->update();
  }
  if (millis() - this->click_millis > this->multiple_click_time && this->changed){
    this->changed = false;
    return this->count;
  }else{
    return 0;
  }
}