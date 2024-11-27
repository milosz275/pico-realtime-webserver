#include "ssi.h"

#include <stdint.h>
#include "hardware/adc.h"
#include "pico/cyw43_arch.h"
#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "lwipopts.h"
#include "cgi.h"

const char* __not_in_flash("httpd") ssi_example_tags[] =
{
    "hello",    // 0
    "state1",   // 1
    "bg1",      // 2
    "temp1"     // 3
};

uint16_t __time_critical_func(ssi_handler)(int iIndex, char *pcInsert, int iInsertLen)
{
    size_t printed;
    bool onboard_led_state = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN);
    switch (iIndex)
    {
        case 0: /* "hello" */
            printed = snprintf(pcInsert, iInsertLen, "Hello World!");
            break;
        case 1: /* state1 */
            if(onboard_led_state)
                printed = snprintf(pcInsert, iInsertLen, "checked");
            else
                printed = snprintf(pcInsert, iInsertLen, " ");
            break;
        case 2: /* bg1 */
            if(onboard_led_state)
                printed = snprintf(pcInsert, iInsertLen, "\"background-color:green;\"");
            else
                printed = snprintf(pcInsert, iInsertLen, "\"background-color:red;\"");
            break;
        case 3: /* temp1 */
            printed = snprintf(pcInsert, iInsertLen, "%f\n", (27.0f - ((adc_read() * 3.3f / (1 << 12)) - 0.706f) / 0.001721f));
            break;
        default: /* unknown tag */
            printed = 0;
            break;
    }
    LWIP_ASSERT("sane length", printed <= 0xFFFF);
    return (uint16_t)printed;
}

void ssi_init()
{
    for (size_t i = 0; i < LWIP_ARRAYSIZE(ssi_example_tags); ++i)
        LWIP_ASSERT("tag too long for LWIP_HTTPD_MAX_TAG_NAME_LEN", strlen(ssi_example_tags[i]) <= LWIP_HTTPD_MAX_TAG_NAME_LEN);

    http_set_ssi_handler(ssi_handler, ssi_example_tags, LWIP_ARRAYSIZE(ssi_example_tags));
}
