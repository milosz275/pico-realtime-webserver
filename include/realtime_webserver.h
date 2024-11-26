#ifndef __REALTIME_WEBSERVER_H
#define __REALTIME_WEBSERVER_H

typedef enum
{
    INIT_SUCCESS,
    STDIO_INIT_FAILURE,
    WIFI_INIT_FAILURE
} init_result;

void vTask_wifi_server(void* pv_param);

#endif // __REALTIME_WEBSERVER
