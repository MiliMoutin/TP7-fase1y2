#pragma once
#include <iostream>
#include <exception>
using namespace std;

class LCDUnableToWriteException : public exception {
public:
	virtual const char * what() const throw() {
		return "LCD error: unable to write";
	}

};