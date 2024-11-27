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
    },
    {
        /* Authentication */
        "/auth.cgi", cgi_handler_auth
    }
};

void cgi_init()
{
    http_set_cgi_handlers(cgi_handlers, 3); // remember to update this
}

const char* cgi_handler_hello_world(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    vGuarded_print("cgi_handler_hello_world called with index %d\n", iIndex);
    return "/index.html";
}

const char* cgi_handler_onboard_led(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    vGuarded_print("cgi_handler_onboard_led called with index %d\n", iIndex);
    // [ ] check authentication
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, !cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN));
    return "/admin.shtml";
}

const char* cgi_handler_auth(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    vGuarded_print("cgi_handler_auth called with index %d\n", iIndex);
    if (iNumParams == 1 && pcParam[0] && strcmp(pcParam[0], "password") == 0 && strcmp(pcValue[0], "0000") == 0)
    {
        vGuarded_print("cgi_handler_auth authentication succeeded\n");
        return "/admin.shtml";
    }
    vGuarded_print("cgi_handler_auth authentication failed\n");
    return "/index.html";
}
