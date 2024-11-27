#ifndef __CGI_H
#define __CGI_H

void cgi_init();

const char* cgi_handler_hello_world(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

const char* cgi_handler_onboard_led(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

const char* cgi_handler_auth(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

#endif // __CGI_H
