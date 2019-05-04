#pragma once
#include "lcd.h"
#define DEVICE 1

class ExternalHandler {
public :
	ExternalHandler();
	~ExternalHandler();
	//escribe en modo instruccion
	void writeIR(BYTE byte);
	//escribe en modo datos
	void writeDR(BYTE byte);
	//falta agregar destructor
private :
	FT_HANDLE handler;
};
