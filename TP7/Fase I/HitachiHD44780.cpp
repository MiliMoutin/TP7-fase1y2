#include "HitachiHD44780.h"

#define CADD_2ND_LAYER 0X0004
#define CADD_LAYER_1ST_BIT 0x0008

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

BasicLCD& HitachiHD44780::operator<<(const unsigned char c) {
	cadd++;
	if (cadd == 33) {
		cadd = 1;
		//falta hacer el "update real" del cursor pero no entendi la instruccion =)
	}
	if (cadd == 18) {
		//falta hacer el "update real" del cursor pero no entendi la instruccion =)
	}
	try {
		this->handler->writeDR(c);
	}
	catch (FT_STATUS e) {
		this->err = e;
	}
	return *this;
}

//tengo del d0 al d6 para el cursor, si los preimeros 3 son para indicar si es la fila 0 o 4 entonces los otros 4 vas de 0 a 16
//sidenote: por ahi entendi como la mierda como es esta parte asi que no se fien al 100%
BasicLCD& HitachiHD44780::operator<<(const unsigned char * c) {
	for (int i = 0; c[i]!=0 ; i++) {
		*this << c[i];
	}
	return *this;
}

bool 
HitachiHD44780::lcdMoveCursorUp()
{	
	union adress {
		int cursor;
		uint8_t layer : 3;

	};
	adress actual_add;
	actual_add.cursor = cadd;
	if (actual_add.cursor > 0)
		return false;
	else
	{
		cadd = cadd | CADD_2ND_LAYER;
		return true;
	}
}
bool 
HitachiHD44780::lcdMoveCursorDown()
{
	union adress {
		int cursor;
		uint8_t layer : 3;

	};
	adress actual_add;
	actual_add.cursor = cadd;
	if (actual_add.cursor < 4)
		return false;
	else
	{
		cadd = cadd - CADD_2ND_LAYER;
		return true;
	}	
}
bool 
 HitachiHD44780::lcdMoveCursorRight()
{
	union adress {
		int cursor;
		struct {
			uint8_t layer : 3;
			uint8_t columns : 4;
		};

	};
	adress actual_add;
	actual_add.cursor = cadd;
	if (actual_add.columns < 16)
	{
		cadd = cadd + CADD_LAYER_1ST_BIT;
		return true;
	}
	else
		return false;
}
bool 
HitachiHD44780::lcdMoveCursorLeft()
{
	union adress {
		int cursor;
		struct {
			uint8_t layer : 3;
			uint8_t columns : 4;
		};

	};
	adress actual_add;
	actual_add.cursor = cadd;
	if (actual_add.columns > 0)
	{
		cadd = cadd - CADD_LAYER_1ST_BIT;
		return true;
	}
	else
		return false;
}
bool 
HitachiHD44780::lcdSetCursorPosition(const cursorPosition pos)
{
	if (pos.row > 0 || pos.row < 1 || pos.column > 0 || pos.column < 15) //Se mueve en 2 filas y 16 columnas
		return false;
	else
	{
		//Seteo la fila
		int new_row = 0;
		new_row = (pos.row << 2);
		//cadd ^ new_row;
		//Seteo la columna
		int new_col = 0;
		new_col = (pos.column << 3);
		//cadd ^ new_col;
		return true;
	}
}

//Se que lo que hice aca es muy trucho... pero bueno, estaba cansado, si ven otra forma de hacerlo por favor corrijanlo
cursorPosition 
HitachiHD44780::lcdGetCursorPosition()
{
	union colsNrows{
		int cursor;
		struct {
			uint8_t layer : 3;
			uint8_t columns : 4;
		};
		
	};
	colsNrows actual_cadd;
	actual_cadd.cursor = cadd;
	int actual_row = actual_cadd.layer;
	int actual_col = actual_cadd.columns;
	cursorPosition actual_pos;
	actual_pos.row = actual_row / 4;
	actual_pos.column = actual_col;
	return actual_pos;
}
void 
HitachiHD44780::lcdUpdateCursor()
{

}
