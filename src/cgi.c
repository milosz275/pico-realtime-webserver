#include "cgi.h"

#include <stdio.h>
#include <string.h>

#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "lwipopts.h"
#include "common.h"
#include "auth.h"

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
    },
    {
        /* Favicon */
        "/favicon.ico", cgi_favicon
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

const char* cgi_handler_auth(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {
    vGuarded_print("cgi_handler_auth called with index %d\n", iIndex);

    // Check if the correct password was provided
    if (iNumParams == 1 && strcmp(pcParam[0], "password") == 0 && strcmp(pcValue[0], ADMIN_PASSWORD) == 0) {
        char user_hash[33];
        generate_hash(user_hash, pcValue[0]); // Generate a unique hash for the user

        add_session(user_hash); // Store the hash in the session table

        // Set the Set-Cookie header to include the session hash
        httpd_resp_set_hdr("Set-Cookie", "session=%s; Path=/; HttpOnly", user_hash);

        vGuarded_print("cgi_handler_auth authentication successful\n");
        return "/admin.shtml"; // Redirect to admin page
    }

    vGuarded_print("cgi_handler_auth authentication failed\n");
    return "/index.html"; // Redirect to login page on failure
}

const char* cgi_handler_onboard_led(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {
    const char* headers = get_http_request_headers(); // Function to get headers

    if (headers) {
        // Extract the "Cookie" header using get_header_value
        const char* cookie_header = get_header_value(headers, "Cookie");

        if (cookie_header) {
            vGuarded_print("Cookie header found: %s\n", cookie_header);

            // Parse the "session" value from the cookie
            const char* session_hash = get_cookie_value(cookie_header, "session");
            if (session_hash) {
                if (is_session_valid(session_hash)) {
                    vGuarded_print("Valid session: %s\n", session_hash);
                    // Perform LED control logic
                    return "/success.shtml"; // Example success page
                } else {
                    vGuarded_print("Invalid session: %s\n", session_hash);
                }
            }
        } else {
            vGuarded_print("No Cookie header found.\n");
        }
    } else {
        vGuarded_print("No headers available.\n");
    }

    // Redirect to login page if session is invalid
    return "/login.shtml";
}

const char* cgi_favicon(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    vGuarded_print("cgi_favicon called with index %d\n", iIndex);
    return "/favicon.ico";
}
