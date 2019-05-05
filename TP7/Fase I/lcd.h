#pragma once
#include <iostream>
#include <Windows.h>
#ifndef FTD2XX_EXPORTS
#define FTD2XX_EXPORTS
#endif
#include "ftd2xx.h"
#include <chrono>
#include <thread>

using namespace std;

#define STANDART_WAIT_T 2
#define DEVICE_NUM 1

//Pines físicos del puerto
#define PORT_P0 0
#define PORT_P1 1
#define PORT_P2 2
#define PORT_P3 3
#define PORT_P4 4
#define PORT_P5 5
#define PORT_P6 6
#define PORT_P7 7

//Funciones de pines de control
#define LCD_E (1 << PORT_P0) 
#define LCD_RS (1 << PORT_P1) 
#define LCD_D4 (1 << PORT_P4) 
#define LCD_D5 (1 << PORT_P5) 
#define LCD_D6 (1 << PORT_P6) 
#define LCD_D7 (1 << PORT_P7)

//Máscaras
#define ENTER (1 << PORT_P0) 
#define R_SELECT (1 << PORT_P1) 
#define B0 (1 << PORT_P4)
#define B1 (1 << PORT_P5)
#define B2 (1 << PORT_P6)
#define B3 (1 << PORT_P7)
#define NIBBLE_BITS (B0|B1|B2|B3)
#define BUS_BYTE (ENTER|R_SELECT|NIBBLE_BITS)
#define NON_USED_BITS ~(BUS_BYTE)

//Funciones de línea
#define LCD_ENTER_ON (LCD_E)			//Activo alto, se prende en 1 y se apaga en 0
#define LCD_ENTER_OFF (LCD_E ^ LCD_E) 
#define LCD_RS_ON (LCD_RS ^ LCD_RS)		//Activo bajo, toma datos en 1 y para enviar instrucciones usa el 0
#define LCD_RS_OFF (LCD_RS)

//Setear bits de control
#define UNSET_ENABLE 0xFE  //pone un 0 en el bit 0 usando un and 
#define SET_ENABLE 0x01 // pone un 1 en el bit 0 usando un or
#define SET_RS 0x02  //pone en 1 el bit 1 usando un or
#define UNSET_RS 0xFC  //pone en 0 en el bit 1 usando un and

//para obtener el MSB hago un or GET_MSB
#define GET_MSB 0xF0

//Instrucciones del LCD
#define FUNC_SET_EIGHTBITS 0x03
#define FUNC_SET_FOURBITS 0x02
#define FUNC_SET_L2_F0 0x08
#define LCD_CLEAR 0x01
#define DISPLAY_ON 0x0C
#define DISPLAY_OFF 0x08
#define CURSOR_ON 0x0A
#define BLINK_ON 0x09
#define DCB_OFF 0x08
#define ENTRY_MODE_SET_UP 0x07
#define CURSOR_CONTINUE 0x2

//Escribe un Nibble
void lcdWriteNibble(FT_HANDLE * deviceHandler, BYTE value);
//pasa el dispositivo a mode 4 bits
void FourBitMode(FT_HANDLE * deviceHandler);
//inicializa al Handler
FT_HANDLE * lcdInit(int iDevice);
//Escribe un byte al IR
void lcdWriteIR(FT_HANDLE * deviceHandler, BYTE valor);
//Escribe un byte al DR
void lcdWriteDR(FT_HANDLE * deviceHandler, BYTE valor);
