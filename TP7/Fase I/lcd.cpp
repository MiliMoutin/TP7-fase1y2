#include "lcd.h"


FT_HANDLE *  lcdInit(int iDevice)
{
	//creo handler  
	FT_STATUS current_status = FT_OTHER_ERROR;
	FT_HANDLE * handler;
	current_status=FT_Open(iDevice, handler);
	//si algo salio mal tiro una excepcion
	if (current_status != FT_OK) {
		throw current_status;
	}
	//cambio a modo 4 bits
	FourBitMode(handler);
	//mas cosas para que todo ande bien
	lcdWriteIR(handler, FUNC_SET_L2_F0);
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	lcdWriteIR(handler, DISPLAY_OFF);
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	lcdWriteIR(handler, LCD_CLEAR);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	lcdWriteIR(handler, ENTRY_MODE_SET_UP);

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

//RS en 1, recibe un BYTE y lo manda al lcd en "modo información"
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
	//seteo el enable en 0 y le doy tiempo a que llegue la señal
	BYTE to_send = UNSET_ENABLE & value;
	current_status = FT_Write(deviceHandler, &to_send, dwBytesToWrite_, &dwBytesToWrite_);
	std::this_thread::sleep_for(std::chrono::milliseconds(STANDART_WAIT_T));
	//mando el primer nibble
	to_send = SET_ENABLE | value;
	current_status = FT_Write(deviceHandler, &to_send, dwBytesToWrite_, &dwBytesToWrite_);
	//Si no se puede escribir tira una excepción 
	if (current_status != FT_OK) {
		throw current_status;
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
	
}

