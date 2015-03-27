#include "SolarSystem.h"

using namespace std;


SolarSystem::SolarSystem() : QWidget() {
	// struct Planet *sun = init_planet("sun", "0", "0", "0", "0", "1988550000000000000000000000000.0", "696342000");
	// struct Planet *earth = init_planet("earth", "149597870000.0", "0", "0", "29780.0", "5972190000000000000000000.0", "6371000");
	// struct Planet *mars = init_planet("mars", "227939100000.0", "0", "0", "24077.0", "641693000000000000000000.0", "6792000");

	planets[0] = new Planet("sun\0", Vector("0", "0"), Vector("0", "0"), "1000000", "100");
	planets[1] = new Planet("earth\0", Vector("50.0", "0"), Vector("0", "10"), "10000", "20");
	planets[2] = new Planet("mars\0", Vector("100", "0"), Vector("0", "20"), "10000", "40");

	G_CONST = "0.0001";

	planetc = 3;

	puts("SolarSystem populated\n");
}

SolarSystem::~SolarSystem() {

}

mpf_class SolarSystem::getG() {
	return G_CONST;
}

int SolarSystem::getPlanetc() {
	return planetc;
}

Planet* SolarSystem::getPlanet(int pos) {
	return planets[pos];
}

// implement adding an elipse for the created planet
void SolarSystem::addPlanet(string name, Vector pos, Vector dof, string mass, string size) {
	// QMessageBox::warning(this, "Error", "errMsg", QMessageBox::Ok);
	
	if (planetc + 1 < 10) {
		planets[planetc] = new Planet(name, pos, dof, mass, size);
		planetc++;

		emit planetAdded();

	} else {
		emit errorOccured("No more room for planets...");
	}
}

void SolarSystem::resetPlanets() {
	for (int i = 0; i < planetc; i++) {
		Planet *p = planets[i];

		p->pos = p->startPos;
		p->dof = p->startDof;
	}

	emit planetsMoved();
}

void SolarSystem::calcGravity(Planet *planet) {
	mpf_class Rx = mpf_class("0", 512);
	mpf_class Ry = mpf_class("0", 512);
	mpf_class r = mpf_class("0", 512);
	mpf_class F = mpf_class("0", 512);
	mpf_class k = mpf_class("0", 512);
	mpf_class t1 = mpf_class("0", 512);
	mpf_class t2 = mpf_class("0", 512);

	Planet *object;
	for (int i = 0; i < planetc; i++) {
		object = planets[i];
		if (planet->name.compare(object->name)) {
			Rx = object->pos.x - planet->pos.x; 
			Ry = object->pos.y - planet->pos.y;

			t1 = Rx * Rx;
			t2 = Ry * Ry;

			t1 += t2;

			r = sqrt(t1);

			t1 = object->mass * planet->mass;
			t1 = t1 / r;

			F = t1 * G_CONST;

			k = F / r;

			t1 = Rx * k;
			t2 = Ry * k;

			t1 = t1 / planet->mass;
			t2 = t2 / planet->mass;

			planet->dof.x += t1;
			planet->dof.y += t2;
		}
	}
}

void SolarSystem::tick() {
	for (int i = 0; i < planetc; i++)
		this->calcGravity(planets[i]);

	for (int i = 0; i < planetc; i++) {
		planets[i]->pos.x += planets[i]->dof.x;
		planets[i]->pos.y += planets[i]->dof.y;
	}

	// emit planetsMoved();
}
