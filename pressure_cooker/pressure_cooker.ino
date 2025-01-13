
#include "cooker_config.h"

#define thermistor_pin 0x01
#define relay_pin      D2

void setup(){
  Serial.begin(9600);
  
  for (uint8_t i=0; i<10; i++) {
    adc_values[i] = 0;
  }
}

void loop(){

}