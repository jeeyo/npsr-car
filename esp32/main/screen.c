#include "npsr_car.h"

#include "u8g2_esp32_hal.h"

void npsr_screen_init()
{
  u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
  u8g2_esp32_hal.sda = OLED_SDA;
  u8g2_esp32_hal.scl = OLED_SCL;
  u8g2_esp32_hal_init(u8g2_esp32_hal);

  u8g2_t u8g2;
  u8g2_Setup_ssd1306_i2c_128x32_univision_f(
    &u8g2,
    U8G2_R0,
    u8g2_esp32_i2c_byte_cb,
    u8g2_esp32_gpio_and_delay_cb
  );

  u8x8_SetI2CAddress(&u8g2.u8x8, 0x78);

  u8g2_InitDisplay(&u8g2);
  u8g2_SetPowerSave(&u8g2, 0);
  u8g2_ClearBuffer(&u8g2);

  u8g2_DrawBox(&u8g2, 0, 26, 80, 6);
  u8g2_DrawFrame(&u8g2, 0,26, 100, 6);

  u8g2_SetFont(&u8g2, u8g2_font_ncenB14_tr);
  u8g2_DrawStr(&u8g2, 5, 17, "Jeeyo");
  u8g2_SendBuffer(&u8g2);
}
