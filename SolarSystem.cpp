#include "SolarSystem.h"

using namespace std;


SolarSystem::SolarSystem() : QWidget() {
	// struct Planet *sun = init_planet("sun", "0", "0", "0", "0", "1988550000000000000000000000000.0", "696342000");
	// struct Planet *earth = init_planet("earth", "149597870000.0", "0", "0", "29780.0", "5972190000000000000000000.0", "6371000");
	// struct Planet *mars = init_planet("mars", "227939100000.0", "0", "0", "24077.0", "641693000000000000000000.0", "6792000");

	selectedPlanetID = -1;
	currentPlanet = Planet("None", "0", "0", "0", "0", "0", "0", "White");

	for (int i = 0; i < MAX_PLANETS; i++)
		planets[i] = NULL;

	planets[0] = new Planet("Sun", "0", "0", "0", "0", "1000000", "100", "Yellow");
	planets[1] = new Planet("Earth", "50", "0", "0", "10", "10000", "20", "Blue");
	planets[2] = new Planet("Mars", "100", "0", "0", "20", "10000", "40", "Red");

	G_CONST = "0.0001";

	frameCount = 0;
	progBarValue = 0;

	ctrlsEnabled = true;
}

SolarSystem::~SolarSystem() {

}

mpf_class SolarSystem::getG() {
	return G_CONST;
}

void SolarSystem::setG(double g) {
	G_CONST = g;
}

Planet* SolarSystem::getPlanet(int id) {
	// currentPlanet = *planets[id];
	// return &currentPlanet;

	return planets[id];
}

void SolarSystem::enableControls() {
	setCtrlState(true);
}

void SolarSystem::setCtrlState(bool state) {
	ctrlsEnabled = state;
	emit ctrlStateChanged();
}

bool SolarSystem::getCtrlState() {
	return ctrlsEnabled;
}

int SolarSystem::getFrameCount() {
	return frameCount;
}

int SolarSystem::getProgBarValue() {
	return progBarValue;
}

void SolarSystem::resetProgBar(int timerDuration) {
	frameCount = timerDuration;
	progBarValue = 0;
	emit progBarChanged();
}

void SolarSystem::setProgBarValue(int frameNr) {
	progBarValue = frameNr;
	emit progBarChanged();
}

void SolarSystem::updatePlanetColor(QString color) {
	if (selectedPlanetID >= 0) {
		Planet *planet = planets[selectedPlanetID];
		planet->color = color.toStdString();

		emit planetChanged(selectedPlanetID);
	}
}

void SolarSystem::addPlanet(string name, Vector pos, Vector dof, mpf_class mass, mpf_class size, string color) {
	int id = -1;
	for (int i = 0; i < MAX_PLANETS; i++) {
		if (planets[i] == NULL) {
			planets[i] = new Planet(name, pos, dof, mass, size, color);
			id = i;
			i = MAX_PLANETS;
		}
	}

	if (id >= 0)
		emit planetAdded(id);
	else
		emit errorOccured("No more room for planets...");
}

void SolarSystem::editPlanet(string name, Vector pos, Vector dof, mpf_class mass, mpf_class size, string color) {
	if (selectedPlanetID >= 0) {
		Planet *planet = planets[selectedPlanetID];
		planet->name = name;
		planet->pos = pos;
		planet->dof = dof;
		planet->mass = mass;
		planet->size = size;
		planet->color = color;

		emit planetChanged(selectedPlanetID);
	} else {
		emit errorOccured("No planet selected");
	}
}

void SolarSystem::deletePlanet(int id) {
	delete planets[id];
	planets[id] = NULL;

	emit planetDeleted(id);
}

void SolarSystem::resetPlanets() {
	for (int i = 0; i < MAX_PLANETS; i++) {
		if (planets[i] != NULL) {
			Planet *p = planets[i];

			p->pos = p->startPos;
			p->dof = p->startDof;
		}
	}

	emit planetsReset();
}

void SolarSystem::setSelectedPlanetID(int id) {
	selectedPlanetID = id;
	emit selectionChanged();
}

int SolarSystem::getSelectedPlanetID() {
	return selectedPlanetID;
}

void SolarSystem::tick() {
	for (int i = 0; i < MAX_PLANETS; i++)
		if (planets[i] != NULL) this->calcGravity(planets[i]);

	for (int i = 0; i < MAX_PLANETS; i++) {
		if (planets[i] != NULL) {
			planets[i]->pos.x += planets[i]->dof.x;
			planets[i]->pos.y += planets[i]->dof.y;
		}
	}
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
	for (int i = 0; i < MAX_PLANETS; i++) {
		if (planets[i] != NULL) {
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
}
