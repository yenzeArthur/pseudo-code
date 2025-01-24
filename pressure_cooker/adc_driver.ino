
#include "cooker_config.h"

#define NTC_R0           100000.0       // Resistance at 25°C from the part number
#define NTC_B            3977.0         // Beta value from the datasheet rt table
#define NTC_T0           298.15         // 25°C in kelvin scale
#define ADC_REF          5.0            // Reference voltage for Arduino Uno after setting REFS0 to 1
#define ADC_RESOLUTION   1023           // since the atmega is a 10 bit resolution

uint8_t index = 0;
uint16_t adc_value;
float avg_adc_value;
float resistance;
float voltage;

bool init_ADC(int analog_pin){
  ADMUX  |= analog_pin;                                                   // We read A0 after setting 0000 to mux
  ADMUX  |= B01000000;                                                    // REFS0 equal to 1
  ADCSRA |= B11000000;                                                    // ADEN and ADSC equal to 1
  return true;
}

void get_ADC_value(){
  while(bit_is_set(ADCSRA, ADSC));
  adc_value = ADCL | (ADCH << 8);
}

void calculate_avg_adc_value(){
  uint8_t new_adc_value = adc_value;
  adc_values[index] = new_adc_value;
  index = (index + 1) % 10;                                                 //flushing out the oldest value

  int sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += adc_values[i];
  }
  avg_adc_value = sum / 10;
}

void update_temperature_value(){
  get_ADC_value();
  calculate_avg_adc_value();
  voltage     =   (avg_adc_value * ADC_REF) / ADC_RESOLUTION;                             //converting ADC value to voltage btn 0 and 5
  resistance  =   (voltage * NTC_R0) / (ADC_REF - voltage);                               //finding the resistance of the thermistor
  device_params.temperature =   1 / (1/NTC_T0 + (1/NTC_B) * log(resistance/NTC_R0));      //steinhart's formula
  device_params.temperature =   device_params.temperature - 273.15;                       //expresing the temperature in celcius scale from kelvin  
}
