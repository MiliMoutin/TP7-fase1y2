#pragma once

#include <iostream>
#include <exception>
#include "ftd2xx.h"
using namespace std;

class LCDUnableToOpenException : public exception {
public:
	LCDUnableToOpenException(FT_STATUS);
	virtual const char * what() const throw() {
		return "LCD error: unable to Open";
	}
	FT_STATUS status() { return this->status; }
private: 
	FT_STATUS status;

};

