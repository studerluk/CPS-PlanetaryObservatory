#ifndef PLANET_H
#define PLANET_H


#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include <string>

#include "Coords.h"


using namespace std;


class Planet {

public:
	Planet(string name, string posX, string posY, string volX, string volY,
			 string mass, string size);
	virtual ~Planet();

	Coords *pos;
	Coords *dof;
	mpf_class mass;
	mpf_class size;
	string name;
};


#endif
