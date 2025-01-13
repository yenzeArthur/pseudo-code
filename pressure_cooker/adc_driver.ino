
#include "cooker_config.h"

bool init_ADC(uint8_t analog_pin){
  ADMUX  |= analog_pin;  // We read A0
  ADMUX  |= B01000000;   // REFS0 equal to 1
  ADCSRA |= B11000000;   // ADEN and ADSC equal to 1
  return true;
}

void get_ADC_value(){
  while(bit_is_set(ADCSRA, ADSC));
  device_params.adc_value = ADCL | (ADCH << 8);
}

void calculate_avg_adc_value(){
  uint8_t new_adc_value = device_params.adc_value;
  adc_values[index] = new_adc_value;
  index = (index + 1) % 10;

  int sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += adc_values[i];
  }
  device_params.avg_adc_value = sum / 10;
}

void get_temperature_value(){
  device_params.voltage = (device_params.avg_adc_value * ADC_REF) / ADC_RESOLUTION;
  device_params.resistance = (device_params.voltage * NTC_R0) / (ADC_REF - device_params.voltage);
  device_params.temperature = 1 / (1/NTC_T0 + (1/NTC_B) * log(device_params.resistance/NTC_R0)); 
  device_params.temperature = device_params.temperature - 273.15;  
}
