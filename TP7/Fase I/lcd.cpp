#include "lcd.h"
#include "LCDUnableToWriteException.h"
#include "LCDUnableToOpenException.h"
#include <cstdio>
#include <chrono>
#include <thread>

using namespace std;

#define STANDART_WAIT_T 2
#define DEVICE_NUM 1

//Pines f�sicos del puerto
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

//M�scaras
#define ENTER (1 << PORT_P0) 
#define R_SELECT (1 << PORT_P1) 
#define B0 (1 << PORT_P4)
#define B1 (1 << PORT_P5)
#define B2 (1 << PORT_P6)
#define B3 (1 << PORT_P7)
#define NIBBLE_BITS (B0|B1|B2|B3)
#define BUS_BYTE (ENTER|R_SELECT|NIBBLE_BITS)
#define NON_USED_BITS ~(BUS_BYTE)

//Funciones de l�nea
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
//Instrucciones del LCD#define FUNC_SET_EIGHTBITS 0x03#define FUNC_SET_FOURBITS 0x02#define FUNC_SET_L2_F0 0x08#define LCD_CLEAR 0x01#define DISPLAY_ON 0x0C#define DISPLAY_OFF 0x08#define CURSOR_ON 0x0A#define BLINK_ON 0x09#define DCB_OFF 0x08#define ENTRY_M_S FT_HANDLE *  lcdInit(int iDevice)
{
	//creo handler  
	FT_STATUS current_status = FT_OTHER_ERROR;
	FT_HANDLE * handler;
	current_status=FT_Open(iDevice, handler);
	if (current_status != FT_OK) {
		throw LCDUnableToOpenException();
	}
	FourBitMode(handler);
	return handler;
}

//RS en 0, recibe un BYTE y lo manda al lcd en "modo instruccion"
void lcdWriteIR(FT_HANDLE * deviceHandler, BYTE valor)
{	//quiero el nibble mas significativo
	BYTE write = valor & GET_MSB;
	lcdWriteNibble(deviceHandler, write & UNSET_RS);
	//ahora quiero el nibble menos significativo
	write = (valor << 4);
	lcdWriteNibble(deviceHandler, write & UNSET_RS);
}

//RS en 1, recibe un BYTE y lo manda al lcd en "modo informaci�n"
void lcdWriteDR(FT_HANDLE * deviceHandler, BYTE valor)
{
	//quiero el nibble mas significativo
	BYTE write = valor & GET_MSB;
	lcdWriteNibble(deviceHandler, write | SET_RS);
	//ahora quiero el nibble menos significativo
	write = (valor << 4);
	lcdWriteNibble(deviceHandler, write | SET_RS);
}



void lcdWriteNibble(FT_HANDLE * deviceHandler, BYTE value) {
	FT_STATUS current_status = FT_OTHER_ERROR;
	DWORD dwBytesToWrite_ = 1;
	//seteo el enable en 0 y le doy tiempo a que llegue la se�al
	BYTE to_send = UNSET_ENABLE & value;
	current_status = FT_Write(deviceHandler, &to_send, dwBytesToWrite_, &dwBytesToWrite_);
	std::this_thread::sleep_for(std::chrono::milliseconds(STANDART_WAIT_T));
	//mando el primer nibble
	to_send = SET_ENABLE | value;
	current_status = FT_Write(deviceHandler, &to_send, dwBytesToWrite_, &dwBytesToWrite_);
	//Si no se puede escribir tira una excepci�n 
	if (current_status != FT_OK) {
		throw LCDUnableToWriteException();
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(STANDART_WAIT_T));
	//mandamos el enable en cero
	to_send = UNSET_ENABLE & value;
	FT_Write(deviceHandler, &to_send, dwBytesToWrite_, &dwBytesToWrite_);
	std::this_thread::sleep_for(std::chrono::milliseconds(STANDART_WAIT_T));

}

void FourBitMode(FT_HANDLE * deviceHandler) {
	lcdWriteNibble(deviceHandler, FUNC_SET_EIGHTBITS);
	std::this_thread::sleep_for(std::chrono::milliseconds(5));
	lcdWriteNibble(deviceHandler, FUNC_SET_EIGHTBITS);
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	lcdWriteNibble(deviceHandler, FUNC_SET_EIGHTBITS);
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	lcdWriteNibble(deviceHandler, FUNC_SET_FOURBITS);
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	lcdWriteIR(deviceHandler, FUNC_SET_L2_F0);
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	lcdWriteIR(deviceHandler, DISPLAY_OFF);
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	lcdWriteIR(deviceHandler, LCD_CLEAR);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	//faltaria ultima instruccion que no se como es
}

