
#include "cooker_config.h"

bool init_ADC(int analog_pin){
  ADMUX  |= analog_pin;  // We read A0 after setting 0000 to mux
  ADMUX  |= B01000000;   // REFS0 equal to 1
  ADCSRA |= B11000000;   // ADEN and ADSC equal to 1
  return true;
}

void get_ADC_value(){
  while(bit_is_set(ADCSRA, ADSC));
  device_params.adc_value = ADCL | (ADCH << 8);
  return true;
}

void calculate_avg_adc_value(){
  uint8_t new_adc_value = device_params.adc_value;
  adc_values[index] = new_adc_value;
  index = (index + 1) % 10;                                 //flushing out the oldest value

  int sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += adc_values[i];
  }
  device_params.avg_adc_value = sum / 10;
}

void get_temperature_value(){
  device_params.voltage = (device_params.avg_adc_value * ADC_REF) / ADC_RESOLUTION;                 //converting ADC value to voltage btn 0 and 5
  device_params.resistance = (device_params.voltage * NTC_R0) / (ADC_REF - device_params.voltage);  //finding the resistance of the thermistor
  device_params.temperature = 1 / (1/NTC_T0 + (1/NTC_B) * log(device_params.resistance/NTC_R0));    //steinhart's formula
  device_params.temperature = device_params.temperature - 273.15;                                   //expresing the temperature in celcius scale from kelvin
  return true;  
}
