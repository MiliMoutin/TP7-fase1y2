#pragma once
#include <cstdio>
#include <exception>

class LCDUnableToWriteException : public exception {
public:
	virtual const char * what() const throw() {
		return "LCD Error: unable to write";
	}
};
