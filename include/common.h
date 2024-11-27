#ifndef __COMMON_H
#define __COMMON_H

#include <pico/stdlib.h>

#define ADMIN_PASSWORD "0000"
#define MAX_HEADERS_LEN 1024
#define MAX_COOKIE_VALUE 128 // Max size of the cookie value

void init_common();

void vGuarded_print(const char* format, ...);

// Helper function to find query parameter value
const char* get_query_param(const char *query_string, const char *param_name);

const char* get_header_value(const char* headers, const char* header_name);

/**
 * Extract the session hash from the "Cookie" header.
 */
const char* get_cookie_value(const char* cookie_header, const char* key);

/**
 * Function to set a header in the HTTP response.
 */
void httpd_resp_set_hdr(const char* header_name, const char* header_format, const char* header_value);

void parse_http_headers(const char *request);

const char* get_http_request_headers();

#endif // __COMMON_H
