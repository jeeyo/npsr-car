#include "npsr_car.h"

#define GPS_TAG "GPS"

static gps_t __latest_gps_data;

const gps_t *npsr_get_latest_gps_data()
{
  return &__latest_gps_data;
}

static void gps_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
  switch (event_id)
  {
  case GPS_UPDATE:
    memcpy(&__latest_gps_data, (gps_t *)event_data, sizeof(gps_t));
    break;
  case GPS_UNKNOWN:
    /* print unknown statements */
    ESP_LOGW(GPS_TAG, "Unknown statement: %s", (char *)event_data);
    break;
  default:
    break;
  }
}

void npsr_gps_init()
{
  nmea_parser_config_t uart_config = {
    .uart = {
      .uart_port = GPS_UART_NUM,
      .rx_pin = GPS_RX_PIN,
      .baud_rate = 9600,
      .data_bits = UART_DATA_8_BITS,
      .parity = UART_PARITY_DISABLE,
      .stop_bits = UART_STOP_BITS_1,
      .event_queue_size = 16
    }
  };
  nmea_parser_handle_t nmea_hdl = nmea_parser_init(&uart_config);
  nmea_parser_add_handler(nmea_hdl, gps_event_handler, NULL);
}
