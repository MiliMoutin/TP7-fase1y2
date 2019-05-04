#pragma once
#ifndef LED_H
#define LED_H
#include "ftd2xx.h"

FT_HANDLE * deviceHandler lcdInit(int iDevice);
//Escribe un byte al IR
void lcdWriteIR(FT_HANDLE * deviceHandler, BYTE valor);
//Escribe un byte al DR
void lcdWriteDR(FT_HANDLE * deviceHandler, BYTE valor);

#endif