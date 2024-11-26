#ifndef __SSI_H
#define __SSI_H

#include <stdint.h>
#include <pico/platform/sections.h>

void ssi_init();

__attribute__((section(".time_critical.ssi_handler"))) uint16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen);

#endif // __SSI_H
