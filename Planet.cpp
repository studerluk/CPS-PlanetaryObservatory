#include "Coords.h"
#include "Planet.h"

using namespace std;


Planet::Planet(string name, string posX, string posY, string volX, string volY,
				 string mass, string size) {

	this->name = name;
	this->size = mpf_class(size, 512);
	this->mass = mpf_class(mass, 512);
	this->pos = new Coords(posX, posY);
	this->dof = new Coords(volX, volY);

	cout << this->name << " initialized\n";
}

Planet::~Planet() {

}
