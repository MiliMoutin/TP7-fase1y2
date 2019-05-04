#pragma once
#include "BasicLCD.h"
#include "ExternalHandler.h"

class HitachiHD44780 : public BasicLCD {
public:
	HitachiHD44780();
	~HitachiHD44780();
	virtual bool lcdInitOk() = 0;
	virtual FT_STATUS lcdGetError() = 0;
	virtual bool lcdClear() = 0;
	virtual bool lcdClearToEOL() = 0;
	virtual BasicLCD& operator<<(const unsigned char c) = 0;
	virtual BasicLCD& operator<<(const unsigned char * c) = 0;
	virtual bool lcdMoveCursorUp() = 0;
	virtual bool lcdMoveCursorDown() = 0;
	virtual bool lcdMoveCursorRight() = 0;
	virtual bool lcdMoveCursorLeft() = 0;
	virtual bool lcdSetCursorPosition(const cursorPosition pos) = 0;
	virtual cursorPosition lcdGetCursorPosition() = 0;


private: 
	ExternalHandler * handler;
	FT_STATUS err;
};
