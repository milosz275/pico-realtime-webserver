#ifndef __REALTIME_WEBSERVER_H
#define __REALTIME_WEBSERVER_H

/**
 * Main WiFi task running network initialization and server loop.
 * 
 * @param pv_param Task parameters remain unused.
 */
void vTask_wifi_server(void* pv_param);

/**
 * Task printing onboard temperature to stdout.
 * 
 * @param pv_param Task parameters remain unused.
 */
void vTask_print_temp(void* pv_param);

#endif // __REALTIME_WEBSERVER
