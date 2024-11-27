#ifndef __AUTH_H
#define __AUTH_H

#include <pico/stdlib.h>

#define MAX_SESSIONS 10  // Limit the number of concurrent sessions
#define SESSION_TIMEOUT 300  // Session timeout in seconds

// Structure to store authenticated user sessions
typedef struct
{
    char hash[33];  // MD5 hash or similar
    uint32_t expiry; // Expiry timestamp (e.g., seconds since boot)
} auth_session;

// Helper function to generate a unique hash (dummy hash example)
void generate_hash(char *output, const char *input);

// Check if a session is valid
bool is_session_valid(const char *hash);

// Add a new session
void add_session(const char *hash);

#endif // __AUTH_H
