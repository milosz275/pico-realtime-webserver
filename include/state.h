#ifndef __STATE_H
#define __STATE_H

#include <signal.h>

#include "FreeRTOS.h"
#include "semphr.h"

/**
 * The program state structure used to store the state of the program.
 *
 * @param exit_flag The exit flag of the program.
 * @param exit_flag_mutex The mutex to protect the exit flag.
 * @param connection_flag The WiFi connection status flag.
 * @param connection_flag_mutex The mutex to protect the WiFi connection status flag.
 */
typedef struct
{
    volatile sig_atomic_t exit_flag;
    SemaphoreHandle_t exit_flag_mutex;
    volatile sig_atomic_t connection_flag;
    SemaphoreHandle_t connection_flag_mutex;
} program_state;

/**
 * Initialize the program state.
 */
void init_program_state();

/**
 * Set the exit flag.
 *
 * @param flag The flag to set.
 */
void set_exit_flag(volatile sig_atomic_t flag);

/**
 * Get the exit flag.
 *
 * @return The exit flag.
 */
sig_atomic_t get_exit_flag();

/**
 * Set the connection flag.
 *
 * @param flag The flag to set.
 */
void set_connection_flag(volatile sig_atomic_t flag);

/**
 * Get the connection flag.
 *
 * @return The exit flag.
 */
sig_atomic_t get_connection_flag();

#endif // __STATE_H
