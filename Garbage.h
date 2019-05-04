#pragma once
void lcdWriteNibble(FT_HANDLE * deviceHandler, BYTE value) {
	FT_STATUS current_status = FT_OTHER_ERROR;
	//mando el primer nibble 
	BYTE to_send = LCD_D4 | value;
	current_status = lcdWriteBit(deviceHandler, to_send);
	//Si no se puede escribir tira una excepción 
	if (current_status != FT_OK) {
		throw LCDUnableToWriteException();
	}
	//le doy un rato al lcd para que llegue la señal y empiezo a mandar el otro bit
	std::this_thread::sleep_for(std::chrono::milliseconds(STANDART_WAIT_T));
	//repito lo anterior para los proximos 3 bits
	to_send = LCD_D5 | value;
	current_status = lcdWriteBit(deviceHandler, to_send);
	if (current_status != FT_OK) {
		throw LCDUnableToWriteException();
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(STANDART_WAIT_T));

	to_send = LCD_D6 | value;
	current_status = lcdWriteBit(deviceHandler, to_send);
	if (current_status != FT_OK) {
		throw LCDUnableToWriteException();
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(STANDART_WAIT_T));

	to_send = LCD_D7 | value;
	current_status = lcdWriteBit(deviceHandler, to_send);
	if (current_status != FT_OK) {
		throw LCDUnableToWriteException();
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(STANDART_WAIT_T));

}