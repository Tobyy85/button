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

        if (this->clicks_index < this->max_values){
            this->clicks_index++;
        }else{
            this->clicks_index = 1;
            this->reset = true;
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

    // sort the values by logic in clicks_time.txt

  }
  return new_arr;
}



String Button::get(){
    long** sorted_values = get_sorted_values(this->clicks_time, this->clicks_index);
    for (int i = 0; i < 3; i++){
      Serial.print("clicks_time[");
      Serial.print(i);
      Serial.print("] = [");
      Serial.print(this->clicks_time[i][0]);
      Serial.print(", ");
      Serial.print(this->clicks_time[i][1]);
      Serial.println("]");

    }

    for (int i = 0; i < max_values; i++){
      delete[] sorted_values[i];
    }
    delete[] sorted_values;
    return "None";
}

String Button::get_position(){
    return this->position;
}