#include "HitachiHD44780.h"

HitachiHD44780::HitachiHD44780() {
	this->err = FT_OK;
	try {
		this->handler = new ExternalHandler();
	}
	catch (FT_STATUS status) {
		this->err = status;
	}
	this->cadd = 1;
}

HitachiHD44780::~HitachiHD44780() {
	delete this->handler;
}


bool HitachiHD44780::lcdInitOk() {
	return this->err == FT_OK;
}

bool HitachiHD44780::lcdClear() {
	bool everythingOK = true;
	try {
		this->handler->writeIR(LCD_CLEAR);
	}
	catch (FT_STATUS status) {
		this->err = status;
		everythingOK = false;
	}
	cadd = 1;
	return everythingOK;
}

FT_STATUS HitachiHD44780::lcdGetError() {
	return this->err;
}

//BasicLCD& HitachiHD44780::operator<<(const unsigned char c) {

//}





