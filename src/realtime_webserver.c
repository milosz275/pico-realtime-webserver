#include "realtime_webserver.h"

#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include <pico/multicore.h>
#include <hardware/adc.h>
#include <lwip/netif.h>
#include "lwip/apps/httpd.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "lwipopts.h"
#include "wifi_credentials.h"
#include "cgi.h"
#include "ssi.h"
#include "common.h"

void vTask_wifi_server(void* pv_param)
{
    vGuarded_print("Connecting to WiFi...\n");
    cyw43_arch_wifi_connect_async(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK);
    
    while (cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA) != CYW43_LINK_UP)
    {
        if (cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA) == CYW43_LINK_FAIL)
        {
            vGuarded_print("Failed to connect to WiFi. Retrying...\n");
            cyw43_arch_wifi_connect_async(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
    vGuarded_print("Connected %s on core %d.\n", pcTaskGetName(NULL), get_core_num());
    extern cyw43_t cyw43_state;
    uint32_t ip_addr = cyw43_state.netif[CYW43_ITF_STA].ip_addr.addr;
    vGuarded_print("IP Address: %lu.%lu.%lu.%lu\n", ip_addr & 0xFF, (ip_addr >> 8) & 0xFF, (ip_addr >> 16) & 0xFF, ip_addr >> 24);
    
    httpd_init();
    ssi_init();
    cgi_init();

    while (true)
        vTaskDelay(100 / portTICK_PERIOD_MS);
}
