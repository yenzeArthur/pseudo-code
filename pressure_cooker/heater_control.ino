
#include "cooker_config.h"

bool heater_init(){
  pinMode(relay_pin, OUTPUT);
  return true;
}

HEATER_STATES heater_control(int current_state){
  int state = current_state;
  switch (state){
    case ON:
      digitalWrite(relay_pin, HIGH);
    break;
    case OFF:
      digitalWrite(relay_pin, LOW);
    break;
    default:
      Serial.println("that is an unknown state!");
  }
}