#include "common.h"

#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/adc.h>
#include <string.h>

#include "lwip/apps/httpd.h"
#include "lwip/apps/httpd_opts.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

SemaphoreHandle_t print_mutex = NULL;

static char response_headers[256]; // Adjust size as needed

static char http_request_headers[MAX_HEADERS_LEN] = {0};

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

const char* get_query_param(const char *query_string, const char *param_name)
{
    static char param_value[128]; // Buffer to store the parameter value (adjust size as needed)
    param_value[0] = '\0'; // Clear buffer

    if (!query_string || !param_name)
    {
        return NULL;
    }

    size_t param_len = strlen(param_name);
    const char *p = query_string;

    while ((p = strstr(p, param_name)) != NULL)
    {
        // Ensure this is a standalone parameter name (followed by '=')
        if (p[param_len] == '=')
        {
            p += param_len + 1; // Move pointer to the start of the value
            size_t i = 0;
            while (*p != '&' && *p != '\0' && i < sizeof(param_value) - 1)
            {
                param_value[i++] = *p++;
            }
            param_value[i] = '\0'; // Null-terminate the value
            return param_value;
        }
        p++; // Move past the current match
    }

    return NULL; // Parameter not found
}

const char* get_header_value(const char* headers, const char* header_name) {
    static char header_value[MAX_COOKIE_VALUE];
    header_value[0] = '\0'; // Clear the buffer

    if (!headers || !header_name) {
        return NULL;
    }

    // Look for the header name in the headers
    const char* header_start = strstr(headers, header_name);
    if (header_start) {
        // Move to the value part of the header (after ": ")
        header_start += strlen(header_name);
        if (*header_start == ':') {
            header_start++; // Skip the colon
            while (*header_start == ' ') {
                header_start++; // Skip spaces
            }

            // Copy the value until the end of the line
            size_t i = 0;
            while (*header_start != '\r' && *header_start != '\n' &&
                   *header_start != '\0' && i < sizeof(header_value) - 1) {
                header_value[i++] = *header_start++;
            }
            header_value[i] = '\0'; // Null-terminate the string
            return header_value;
        }
    }
    return NULL; // Header not found
}

const char* get_cookie_value(const char* cookie_header, const char* key) {
    static char cookie_value[MAX_COOKIE_VALUE];
    cookie_value[0] = '\0'; // Clear the buffer

    if (!cookie_header || !key) {
        return NULL;
    }

    // Look for the cookie key in the Cookie header
    const char* key_start = strstr(cookie_header, key);
    if (key_start) {
        key_start += strlen(key);
        if (*key_start == '=') {
            key_start++; // Skip the '='
            size_t i = 0;
            while (*key_start != ';' && *key_start != '\0' &&
                   i < sizeof(cookie_value) - 1) {
                cookie_value[i++] = *key_start++;
            }
            cookie_value[i] = '\0'; // Null-terminate the string
            return cookie_value;
        }
    }
    return NULL; // Cookie not found
}

void httpd_resp_set_hdr(const char* header_name, const char* header_format, const char* header_value) {
    if (header_name && header_format && header_value) {
        // Format the header and append it to the response_headers buffer
        snprintf(response_headers, sizeof(response_headers), "%s: %s\r\n", header_name, header_format);
        snprintf(response_headers + strlen(response_headers), sizeof(response_headers) - strlen(response_headers), header_value);
    }
}

void parse_http_headers(const char *request) {
    const char *header_start = strstr(request, "\r\n") + 2; // After the request line
    const char *header_end = strstr(request, "\r\n\r\n"); // End of headers
    if (header_start && header_end && (header_end - header_start) < MAX_HEADERS_LEN) {
        size_t headers_len = header_end - header_start;
        strncpy(http_request_headers, header_start, headers_len);
        http_request_headers[headers_len] = '\0'; // Null-terminate
    }
}

const char* get_http_request_headers() {
    return http_request_headers;
}
