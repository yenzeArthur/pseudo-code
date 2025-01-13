
#include "cooker_config.h"

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

