
#include "cooker_config.h"
#include <math.h>

#define thermistor_pin 0x00 // connects to A0 via mux. 
#define relay_pin      2

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

  switch(current_cooker_state){
    case INIT:
      get_ADC_value();
      calculate_avg_adc_value();
      get_temperature_value();
      if(device_params.temperature > 25 && (device_params.temperature == device_params.boiling_point)){
        current_cooker_state = SIMMERING;
      }
      current_cooker_state = HEATING;
      delay(100);
    break;

    case HEATING:
      get_ADC_value();
      calculate_avg_adc_value();
      get_temperature_value();
      if(device_params.temperature > 25 && (device_params.temperature == device_params.boiling_point)){
        heater_control(ON);
        if(get_boiling_point()){
          current_cooker_state = SIMMERING;
        }
        else{
          current_cooker_state = HEATING;
        }
      }
      delay(100);
    break;

    case SIMMERING:
      float current_temperature = device_params.temperature;

      get_ADC_value();
      calculate_avg_adc_value();
      get_temperature_value();

      if(device_params.temperature > 25 && (device_params.temperature == device_params.boiling_point)){
        if (current_temperature <= device_params.boiling_point - 10.0) {
          heater_control(ON);  
        } 
        else if (current_temperature >= device_params.boiling_point + 10.0) {
          heater_control(OFF); 
        }
      }
      delay(100);
    break;

    case ERROR:
      Serial.println("Error occurred. Check system!");
      heater_control(OFF); 
      while(1);
    break;
  }
}

bool get_boiling_point(){
  float current_temperature = device_params.temperature;
  float temperature_difference = current_temperature - previous_temperature;
  
  if ((temperature_difference < 0.1) && (temperature_difference > -0.1)) {
    previous_temperature = current_temperature;
    return true;
  } else {
    previous_temperature = current_temperature;
    return false;
  }
}
