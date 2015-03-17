#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H


#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include <string>

#include "Planet.h"


using namespace std;


class SolarSystem {

public:
	SolarSystem();
	virtual ~SolarSystem();

	void tick(int count);
	Planet *planets[10];

private:
	int planetc;

	mpf_class G_CONST;

	void movePlanet(Planet*);
	void calcGravity(Planet*);

};

#endif
