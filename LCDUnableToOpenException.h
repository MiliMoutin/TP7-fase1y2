#pragma once
#include <cstdio>
#include <exception>

class LCDUnableToOpenException : public exception {
public:
	virtual const char * what() const throw() { return 'LCD Error: unable to open'; }
};
