#ifndef PLANET_H
#define PLANET_H


#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include <string>

#include "Vector.h"


using namespace std;


class Planet {

public:
	Planet();
	Planet(string, Vector, Vector, string, string);
	~Planet();

	string name;
	mpf_class mass;
	mpf_class size;

	Vector startPos;
	Vector startDof;

	Vector pos;
	Vector dof;
	
};


#endif
