
#include "cooker_config.h"

#define thermistor_pin B00000100
#define relay_pin      D2

void setup(){

}

void loop(){

}

bool init_ADC(uint8_t analog_pin){
  ADMUX  |= analog_pin;  // We read A4
  ADMUX  |= B01000000;   // REFS0 equal to 1
  ADCSRA |= B11000000;   // ADEN and ADSC equal to 1
  return true;
}

void get_ADC_value(){
  while(bit_is_set(ADCSRA, ADSC));
  adc_value = ADCL | (ADCH << 8);
}