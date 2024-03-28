//TODO - add option to wait before showing single click if it's not a double or triple click

#include "Button.h"

Button::Button(int pin, bool input_pullup){
  this->pin = pin;
  this->input_pullup = input_pullup;
  if (input_pullup){
    pinMode(pin, INPUT_PULLUP);
  }else{
    pinMode(pin, INPUT);
  }
}

void Button::update(){
  if (this->input_pullup){
    this->state = (digitalRead(this->pin) == LOW);
  }else{
    this->state = (digitalRead(this->pin) == HIGH);
  }
    
  if (this->state && !this->last_state){
    this->clicks_time[this->clicks_index][0] = millis();
    this->position = "UP";
  }
  if (!this->state && this->last_state){
    this->clicks_time[this->clicks_index][1] = millis();
    this->position = "DOWN";
    this->returned = false;
    if (this->clicks_index < this->max_values-1){
      this->clicks_index++;
    }else{
      this->clicks_index = 0;
    }
  }
  this->last_state = state;
}

long** Button::get_sorted_values(unsigned long time_arr[][2], int current_index){
  long** new_arr = new long*[this->max_values];
  for (int i = 0; i < this->max_values; i++){
    new_arr[i] = new long[2];
  }
  
  for (int i = current_index-1, j = 0; i > current_index - this->max_values-1; i--, j++){
    int index = i;
    if (i < 0){
      index = this->max_values + i;
    }
    new_arr[j][0] = time_arr[index][0];
    new_arr[j][1] = time_arr[index][1];
  }
  return new_arr;
}

bool Button::is_long_click(long** sorted_values){
  return sorted_values[0][1] - sorted_values[0][0] >= this->long_click;
}

bool Button::is_single_click(long** sorted_values){
  int difference = sorted_values[0][1] - sorted_values[0][0];
  return 0 < difference && difference < this->long_click;
}

bool Button::is_double_click(long** sorted_values){
  return sorted_values[0][0] - sorted_values[1][1] < this->multiple_click;
}

bool Button::is_triple_click(long** sorted_values){
  return sorted_values[0][0] - sorted_values[1][1] < this->multiple_click && sorted_values[1][0] - sorted_values[2][1] < this->multiple_click;
}

bool Button::is_press_and_hold(long** sorted_values){
  int difference = sorted_values[1][1] - sorted_values[1][0];
  bool is_single = 0 < difference && difference < this->long_click;
  bool is_double = sorted_values[0][0] - sorted_values[1][1] < this->multiple_click;
  bool is_long = sorted_values[0][1] - sorted_values[0][0] >= this->long_click;
  return is_single && is_double && is_long; 
}

String Button::get(bool wait_for_multiple_click){
  update();
  long** sorted_values = get_sorted_values(this->clicks_time, this->clicks_index);
  String click_type = "NO CLICK";

  if (is_press_and_hold(sorted_values) && !this->returned){ //press and hold
    this->returned = true;
    click_type = "PRESS AND HOLD";
  }else if (is_long_click(sorted_values) && !this->returned){ //long click
      this->returned = true;
      click_type = "LONG CLICK";
  }else{
    if (wait_for_multiple_click){
      if (is_triple_click(sorted_values) && !this->returned){ //triple click
        this->returned = true;
        click_type = "TRIPLE CLICK";
      }else if (is_double_click(sorted_values) && !this->returned){ //double click
        this->returned = true;
        click_type = "DOUBLE CLICK";
        double__return_single = false;
      }else if (is_single_click(sorted_values)){ //single click
        if (millis() - sorted_values[0][1] >= this->multiple_click && double__return_single){
          if (!this->returned){
            this->returned = true;
            click_type = "SINGLE CLICK";
          }
        }else{
          double__return_single = true;
        }
      }
    }else{
      if (is_triple_click(sorted_values) && !this->returned){ //triple click
        this->returned = true;
        click_type = "TRIPLE CLICK";
      }else if (is_double_click(sorted_values) && !this->returned){ //double click
        this->returned = true;
        click_type = "DOUBLE CLICK";
      }else if (is_single_click(sorted_values) && !this->returned){ //single click
        this->returned = true;
        click_type = "SINGLE CLICK";
      }
    }
  }

  for (int i = 0; i < max_values; i++){
    delete[] sorted_values[i];
  }
  delete[] sorted_values;
  return click_type;
}

bool Button::is_pressed(){
  update();
  return this->state;
}

String Button::get_position(){
  return this->position;
}