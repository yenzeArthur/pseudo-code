
#ifndef COOKER_CONFIG_H
  #define COOKER_CONFIG_H

  struct DEVICE_PARAMS{
    uint8_t adc_value;
  }

  bool heater_init();
  HEATER_STATES heater_control(int current_state);

#endif