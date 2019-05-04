#pragma once

#include <iostream>
#include <exception>
using namespace std;

class LCDUnableToWriteException : public exception {
public:
	LCDUnableToWriteException(FT_STATUS status) { this->status = status; }
	virtual const char * what() const throw() {
		return "LCD error: unable to write";
	}
    FT_STATUS virtual status() { return this->status; }
private:
	FT_STATUS status;
};