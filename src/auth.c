#include "auth.h"

#include <pico/stdlib.h>
#include <string.h>

#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "lwipopts.h"
#include "common.h"

static auth_session sessions[MAX_SESSIONS] = { 0 };

void generate_hash(char *output, const char *input)
{
    snprintf(output, 33, "%08x", rand()); // Simple random hash; replace with MD5/SHA if needed
}

bool is_session_valid(const char *hash)
{
    for (int i = 0; i < MAX_SESSIONS; ++i)
    {
        if (strcmp(sessions[i].hash, hash) == 0 && sessions[i].expiry > time(NULL))
        {
            return true; // Valid session
        }
    }
    return false;
}

void add_session(const char *hash)
{
    for (int i = 0; i < MAX_SESSIONS; ++i)
    {
        if (sessions[i].expiry == 0 || sessions[i].expiry <= time(NULL))
        {   
            // Find an empty/expired slot
            strncpy(sessions[i].hash, hash, 32);
            sessions[i].expiry = time(NULL) + SESSION_TIMEOUT; // Set expiry time
            break;
        }
    }
}
