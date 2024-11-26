#include "cgi.h"

#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "lwipopts.h"
#include "common.h"

static const tCGI cgi_handlers[] = {
    {
        /* Hello World */
        "/hello_world.cgi", cgi_handler_hello_world
    },
    {
        /* Onboard LED */
        "/onboard_led.cgi", cgi_handler_onboard_led
    }
};

void cgi_init(void)
{
    http_set_cgi_handlers(cgi_handlers, 2); // remember to update this
}

const char* cgi_handler_hello_world(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    vGuarded_print("cgi_handler_hello_world called with index %d\n", iIndex);
    // returning this instead of index.html refreshes the page with new state
    return "/ssi_cgi.shtml";
}

const char* cgi_handler_onboard_led(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    vGuarded_print("cgi_handler_onboard_led called with index %d\n", iIndex);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, !cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN));
    // returning this instead of index.html refreshes the page with new state
    return "/ssi_cgi.shtml";
}
