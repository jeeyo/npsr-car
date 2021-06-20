#include "npsr_car.h"

#include "driver/gpio.h"

uint8_t car_remote_btns[] = {
  GPIO_OUTPUT_IO_0,
  GPIO_OUTPUT_IO_1,
  GPIO_OUTPUT_IO_2,
  GPIO_OUTPUT_IO_3,
};

inline void npsr_car_remote_btnpress(unsigned int btn_index)
{
  gpio_set_level(car_remote_btns[btn_index], 1);
  vTaskDelay(pdMS_TO_TICKS(CAR_REMOTE_PRESS_DELAY_MS));
  gpio_set_level(car_remote_btns[btn_index], 0);
}

void npsr_car_remote_init()
{
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_OUTPUT;
  io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
  io_conf.pull_down_en = 1;
  io_conf.pull_up_en = 0;
  gpio_config(&io_conf);
}
