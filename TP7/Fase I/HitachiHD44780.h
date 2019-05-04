#pragma once
#include "BasicLCD.h"
#include "ExternalHandler.h"

class HitachiHD44780 : public BasicLCD {
public:
	HitachiHD44780();

	//falta el destructor y los metodos aun
private: 
	ExternalHandler handler;
};
