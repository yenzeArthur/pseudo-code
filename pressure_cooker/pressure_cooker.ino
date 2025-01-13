
#include "cooker_config.h"
#include <math.h>

#define thermistor_pin 0x01
#define relay_pin      D2

void setup(){
  Serial.begin(9600);

  if(heater_init()){
    if(init_ADC(thermistor_pin)){
      Serial.println("All drivers are fine!");
    }
  }
  
  for (uint8_t i=0; i<10; i++) {
    adc_values[i] = 0;
  }
}

void loop(){

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