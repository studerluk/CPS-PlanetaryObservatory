#include <iostream>
#include <gmp.h>
#include <gmpxx.h>

#include "SolarSystem.h"
#include "Planet.h"

using namespace std;

int main_2 () {
	SolarSystem milky = SolarSystem();
	milky.tick(10000);

	return 0;
}
