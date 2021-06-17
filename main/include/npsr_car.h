#ifndef _NPSR_CAR_H_
#define _NPSR_CAR_H_

#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "sdkconfig.h"
#include "esp_system.h"
#include "esp_log.h"

#include "nmea_parser.h"

#define GPIO_OUTPUT_IO_0 32    /* Unlock */
#define GPIO_OUTPUT_IO_1 33    /* Lock */
#define GPIO_OUTPUT_IO_2 25    /* Rear trunk */
#define GPIO_OUTPUT_IO_3 26
#define GPIO_OUTPUT_PIN_SEL ((1ULL<<GPIO_OUTPUT_IO_0) | (1ULL<<GPIO_OUTPUT_IO_1) | (1ULL<<GPIO_OUTPUT_IO_2) | (1ULL<<GPIO_OUTPUT_IO_3))
#define CAR_REMOTE_PRESS_DELAY_MS (350)
void npsr_car_remote_init();
void npsr_car_remote_btnpress(unsigned int btn_index);

QueueHandle_t *npsr_get_bluetooth_le_queue();
esp_err_t npsr_bluetooth_le_init();

#define OLED_SDA 5
#define OLED_SCL 4
void npsr_screen_init();

#define GPS_UART_NUM UART_NUM_2
#define GPS_RX_PIN 27
#define GPS_TIME_ZONE (+7)
#define GPS_YEAR_BASE (2000)
const gps_t *npsr_get_latest_gps_data();

#endif /* _NPSR_CAR_H_ */
