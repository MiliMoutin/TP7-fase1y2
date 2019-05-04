#pragma once
#pragma once
#include <iostream>
#include <exception>
using namespace std;

class LCDUnableToOpenException : public exception {
public:
	virtual const char * what() const throw() {
		return "LCD error: unable to Open";
	}
};