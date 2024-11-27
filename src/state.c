#include "state.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/**
 * The program state structure used to store the state of the program.
 *
 * @param exit_flag The exit flag of the program.
 * @param exit_flag_mutex The mutex to protect the exit flag.
 * @param connection_flag The WiFi connection status flag.
 * @param connection_flag_mutex The mutex to protect the WiFi connection status flag.
 */
program_state state = { 0, NULL, 0, NULL };

void init_program_state()
{
    state.exit_flag_mutex = xSemaphoreCreateMutex();
    state.connection_flag_mutex = xSemaphoreCreateMutex();
}

void set_exit_flag(volatile sig_atomic_t flag)
{
    xSemaphoreTake(state.exit_flag_mutex, portMAX_DELAY);
    state.exit_flag = flag;
    xSemaphoreGive(state.exit_flag_mutex);
}

sig_atomic_t get_exit_flag()
{
    xSemaphoreTake(state.exit_flag_mutex, portMAX_DELAY);
    sig_atomic_t flag = state.exit_flag;
    xSemaphoreGive(state.exit_flag_mutex);
    return flag;
}

void set_connection_flag(volatile sig_atomic_t flag)
{
    xSemaphoreTake(state.connection_flag_mutex, portMAX_DELAY);
    state.connection_flag = flag;
    xSemaphoreGive(state.connection_flag_mutex);
}

sig_atomic_t get_connection_flag()
{
    xSemaphoreTake(state.connection_flag_mutex, portMAX_DELAY);
    sig_atomic_t flag = state.connection_flag;
    xSemaphoreGive(state.connection_flag_mutex);
    return flag;
}
