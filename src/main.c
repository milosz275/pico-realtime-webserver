#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include <pico/multicore.h>

#include "realtime_webserver.h"
#include "FreeRTOS.h"
#include "task.h"
#include "lwipopts.h"
#include "common.h"

#define TASK_SIZE 256

int main()
{
    // init
    stdio_init_all();
    if (cyw43_arch_init())
    {
        printf("Wi-Fi init failed");
        return -1;
    }
    cyw43_arch_enable_sta_mode();
    cyw43_wifi_pm(&cyw43_state, cyw43_pm_value(CYW43_NO_POWERSAVE_MODE, 20, 1, 1, 1));

    // tasks
    init_smp();
    vGuarded_print("\033[2J\033[H");

    xTaskCreate(vTask_wifi_server, "WiFi server task", TASK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler();
    while (true) {}
}
