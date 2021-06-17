#include "npsr_car.h"

#include "nvs_flash.h"

void app_main(void)
{
  esp_err_t ret;

  // Initialize NVS.
  ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  // Initialize Bluetooth LE
  ret = npsr_bluetooth_le_init();
  if (ret) {
    printf("Unable to initialize Bluetooth LE\n");
    esp_restart();
  }

  // Initialize Display Screen
  npsr_screen_init();

  // Initialize Car Remote GPIO Interface
  npsr_car_remote_init();

  QueueHandle_t *ble_queue = npsr_get_bluetooth_le_queue();

  while(1)
  {
    uint8_t cmd = 0;
    if (xQueueReceive(*ble_queue, &cmd, pdMS_TO_TICKS(500)) == pdPASS)
    {
      if (cmd > 3) continue;
      npsr_car_remote_btnpress(cmd);
    }

    const gps_t *gps = npsr_get_latest_gps_data();
    printf("%d/%d/%d %d:%d:%d => \r\n"
          "\t\t\t\t\t\tlatitude   = %.05f°N\r\n"
          "\t\t\t\t\t\tlongitude = %.05f°E\r\n"
          "\t\t\t\t\t\taltitude   = %.02fm\r\n"
          "\t\t\t\t\t\tspeed      = %fm/s\r\n",
          gps->date.year + GPS_YEAR_BASE, gps->date.month, gps->date.day,
          gps->tim.hour + GPS_TIME_ZONE, gps->tim.minute, gps->tim.second,
          gps->latitude, gps->longitude, gps->altitude, gps->speed);
  }
}
