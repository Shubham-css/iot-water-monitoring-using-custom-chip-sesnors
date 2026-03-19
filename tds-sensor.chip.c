#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct { pin_t pin; uint32_t attr; } chip_data_t;

void timer_cb(void *data) {
  chip_data_t *chip = (chip_data_t*)data;
  uint32_t val = attr_read(chip->attr);
  
  // Cleanly scale slider (0-1000) to ESP32 voltage (0-3.3V)
  float volts = (val / 1000.0) * 3.3;
  pin_dac_write(chip->pin, volts);
}

void chip_init() {
  chip_data_t *chip = malloc(sizeof(chip_data_t));
  chip->attr = attr_init("tdsValue", 200);
  chip->pin = pin_init("OUT0", ANALOG);
  const timer_config_t config = { .callback = timer_cb, .user_data = chip };
  timer_start(timer_init(&config), 100, true);
}