#include "Button.h"

Button::Button(int pin){
  this->pin = pin;
  pinMode(pin, INPUT_PULLUP);
}

void Button::update(){
  this->state = (digitalRead(this->pin) == LOW);
  if (this->state && !this->last_state){
    this->clicks_time[this->clicks_index][0] = millis();
    this->position = "UP";
  }
  if (!this->state && this->last_state){
    this->clicks_time[this->clicks_index][1] = millis();
    this->position = "DOWN";
    this->returned = false;
    if (this->clicks_index < this->max_values){
      this->clicks_index++;
    }else{
      this->clicks_index = 1;
      this->reached_max_values = true;
    }
  }
  this->last_state = state;
}

long** Button::get_sorted_values(unsigned long time_arr[][2], int current_index){
  long** new_arr = new long*[this->max_values];
  for (int i = 0; i < this->max_values; i++){
    new_arr[i] = new long[2];
  }
  
  for (int i = current_index-1, j = 0; i > current_index - this->max_values -1; i--, j++){
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
  return sorted_values[0][1] - sorted_values[0][0] < this->long_click;
}

bool Button::is_double_click(long** sorted_values){
  
}

bool Button::is_triple_click(long** sorted_values){

}

String Button::get(){
  update();
  long** sorted_values = get_sorted_values(this->clicks_time, this->clicks_index);
  String click_type = "NO CLICK";

  //long click
  if (is_long_click(sorted_values) && !this->returned){
      this->returned = true;
      click_type = "LONG CLICK";
  }else{
    //single click
    if (is_single_click(sorted_values) && !this->returned){
      this->returned = true;
      click_type = "SINGLE CLICK";
    }
  }

  for (int i = 0; i < max_values; i++){
    delete[] sorted_values[i];
  }
  delete[] sorted_values;
  return click_type;
}

String Button::get_position(){
  return this->position;
}