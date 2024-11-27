#include "common.h"

#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/adc.h>
#include "lwip/apps/httpd.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

SemaphoreHandle_t print_mutex = NULL;

void init_common()
{
    print_mutex = xSemaphoreCreateMutex();
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);
}

void vGuarded_print(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    xSemaphoreTake(print_mutex, portMAX_DELAY);
    vprintf(format, args);
    xSemaphoreGive(print_mutex);
    va_end(args);
}
