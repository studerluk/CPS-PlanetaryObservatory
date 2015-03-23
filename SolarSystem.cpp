#include "SolarSystem.h"
#include "Planet.h"

using namespace std;


SolarSystem::SolarSystem() {
	// struct Planet *sun = init_planet("sun", "0", "0", "0", "0", "1988550000000000000000000000000.0", "696342000");
	// struct Planet *earth = init_planet("earth", "149597870000.0", "0", "0", "29780.0", "5972190000000000000000000.0", "6371000");
	// struct Planet *mars = init_planet("mars", "227939100000.0", "0", "0", "24077.0", "641693000000000000000000.0", "6792000");

	Planet *sun = new Planet("sun\0", "0", "0", "0", "0", "1000000", "100");
	Planet *earth = new Planet("earth\0", "50.0", "0", "0", "10", "10000", "20");
	Planet *mars = new Planet("mars\0", "100", "0", "0", "20", "10000", "40");

	this->G_CONST = "0.0001";

	this->planets[0] = sun;
	this->planets[1] = earth;
	this->planets[2] = mars;

	this->planetc = 3;

	puts("SolarSystem populated\n");
}

SolarSystem::~SolarSystem() {

}

void SolarSystem::movePlanet(Planet *planet) {
	planet->pos->x += planet->dof->x;
	planet->pos->y += planet->dof->y;
}

void SolarSystem::calcGravity(Planet *planet) {
	int planetc = this->planetc;
	planetc--;	// Note: I'm shifting 'planetc' by one for the 'for' loop below

	Planet *object;
	mpf_class Rx = mpf_class("0", 512);
	mpf_class Ry = mpf_class("0", 512);
	mpf_class r = mpf_class("0", 512);
	mpf_class F = mpf_class("0", 512);
	mpf_class k = mpf_class("0", 512);
	mpf_class t1 = mpf_class("0", 512);
	mpf_class t2 = mpf_class("0", 512);

	for (int i = planetc; i >= 0; i--) {
		object = this->planets[i];
		if (planet->name.compare(object->name)) {
			Rx = object->pos->x - planet->pos->x; 
			Ry = object->pos->y - planet->pos->y; 

			t1 = Rx * Rx;
			t2 = Ry * Ry;

			t1 += t2;

			r = sqrt(t1);

			t1 = object->mass * planet->mass;
			t1 = t1 / r;

			F = t1 * this->G_CONST;

			k = F / r;

			t1 = Rx * k;
			t2 = Ry * k;

			t1 = t1 / planet->mass;
			t2 = t2 / planet->mass;

			planet->dof->x += t1;
			planet->dof->y += t2;

		}
	}
}

void SolarSystem::tick() {
	for (int i = 0; i < this->planetc; i++)
		this->calcGravity(this->planets[i]);

	for (int i = 0; i < this->planetc; i++)
		this->movePlanet(this->planets[i]);
}
