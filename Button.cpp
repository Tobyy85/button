#include "Button.h"

//TODO add option for max value in get method (default -1 for no limit)

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
    this->state = get_state();


    if (pressed_down()){
      // !  this->last_click_up_millis and this->click_up_millis are one click behind
      this->last_click_down_millis = this->click_down_millis;
      this->click_down_millis = millis();

        if (this->click_down_millis - this->click_up_millis <= this->multiple_click_time){
          this->count++;
        }
        else{
          this->count = 1;
        }
      this->changed = true;
    }

    if (pressed_up()){
      this->last_click_up_millis = this->click_up_millis;
      this->click_up_millis = millis();
    }
}

int Button::get(bool update){  
  if (update){
    this->update();
  }

  unsigned long current_millis = millis();

  if (current_millis - this->click_down_millis > this->multiple_click_time && this->changed){
    // if (!state || (state && current_millis - this->click_down_millis > this->long_click_time)){
      // abych mohlzjisit long click tak potrebuji zjisit jestli furt neni dole ten btn jinak ^ tahle ^ podminka bude splnena a vrati to
      this->changed = false;
      return this->count;

    // }
  }else{
    return 0;
  }
}