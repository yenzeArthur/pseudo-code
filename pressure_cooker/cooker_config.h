
#ifndef COOKER_CONFIG_H
  #define COOKER_CONFIG_H

  #define NTC_R0           100000.0       // Resistance at 25°C from the part number
  #define NTC_B            3977.0         // Beta value from the datasheet rt table
  #define NTC_T0           298.15         // 25°C in kelvin scale
  #define ADC_REF          5.0            // Reference voltage for Arduino Uno after setting REFS0 to 1
  #define ADC_RESOLUTION   1023           // since the atmega is a 10 bit resolution

  int adc_values[10];
  uint8_t index = 0;
  float previous_temperature = 0;

  typedef struct DEVICE_PARAMS{
    uint8_t adc_value;
    float avg_adc_value;
    float temperature;
    float resistance;
    float voltage;
    float boiling_point;
  } DEVICE_PARAMS;

  DEVICE_PARAMS device_params;

  bool heater_init();
  HEATER_STATES heater_control(int current_state);
  bool init_ADC(uint8_t analog_pin);
  void get_ADC_value();
  void calculate_avg_adc_value();
  void get_temperature_value();

#endif