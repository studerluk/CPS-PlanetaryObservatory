#ifndef COORDS_H
#define COORDS_H


#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include <string>

using namespace std;


class Coords {

public:
	Coords(string x, string y);
	virtual ~Coords();

	mpf_class x;
	mpf_class y;

};

#endif