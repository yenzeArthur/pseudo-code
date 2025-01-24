
#ifndef COOKER_CONFIG_H
  #define COOKER_CONFIG_H

  int adc_values[10];

  typedef enum HEATER_STATES{
    ON,
    OFF
  } HEATER_STATES;

  typedef enum COOKER_STATES {
    INIT, 
    HEATING, 
    SIMMERING,
    ERROR 
  } COOKER_STATES;

  typedef struct DEVICE_PARAMS{
    float temperature;
    float boiling_point;
  } DEVICE_PARAMS;

  DEVICE_PARAMS device_params;

  bool heater_init();
  HEATER_STATES heater_control(int current_state);
  bool init_ADC(uint8_t analog_pin);
  void update_temperature_value();

#endif