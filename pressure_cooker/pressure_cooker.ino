
#include "cooker_config.h"
#include <math.h>

#define thermistor_pin 0x00                                 // connects to A0 via mux. 
#define relay_pin      2
float previous_temperature = 0;

COOKER_STATES current_cooker_state;

void setup(){
  Serial.begin(9600);

  if(heater_init()){
    if(init_ADC(thermistor_pin)){
      Serial.println("All drivers are fine!");
      for (uint8_t i=0; i<10; i++) {
        adc_values[i] = 0;
      }
      current_cooker_state = INIT;
    }
  }
  else{
    current_cooker_state = ERROR;
  }
}

void loop(){

  update_temperature_value();

  switch(current_cooker_state){

    case INIT:
      if((device_params.temperature > 25) && (device_params.temperature == device_params.boiling_point)){
        current_cooker_state = SIMMERING;
      }
      else{
        current_cooker_state = HEATING;
      }
    break;

    case HEATING:
      if((device_params.temperature != device_params.boiling_point)){
        heater_control(ON);
        if(get_boiling_point()){
          current_cooker_state = SIMMERING;
        }
        else{
          current_cooker_state = HEATING;
        }
      }
    break;

    case SIMMERING:
      float current_temperature = device_params.temperature;
      if (current_temperature <= (device_params.boiling_point - 2.0)) {
        heater_control(ON);  
      } 
      else if (current_temperature >= (device_params.boiling_point + 2.0)) {
        heater_control(OFF); 
      }
    break;

    case ERROR:
      Serial.println("Error occurred. Check system!");
      heater_control(OFF); 
      while(1);
    break;
  }
  delay(100);
}

bool get_boiling_point(){
  float current_temperature = device_params.temperature;
  float temperature_difference = current_temperature - previous_temperature;
  
  if ((temperature_difference < 0.1) && (temperature_difference > -0.1)) {
    device_params.boiling_point = device_params.temperature;
    previous_temperature = current_temperature;
    return true;
  } else {
    previous_temperature = current_temperature;
    return false;
  }
}

