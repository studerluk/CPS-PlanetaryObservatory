
#include "Planet.h"

using namespace std;


Planet::Planet() {
	
}

Planet::Planet(string name, string posx, string posy, string dofx, string dofy, string mass, string size) {

	this->name = name;
	this->pos = Vector(posx, posy);
	this->dof = Vector(dofx, dofy);

	this->size = mpf_class(size, 512);
	this->mass = mpf_class(mass, 512);

	this->startPos = pos;
	this->startDof = dof;

	cout << this->name << " initialized\n";
}

Planet::Planet(string name, Vector pos, Vector dof, mpf_class mass, mpf_class size) {

	this->name = name;
	this->pos = pos;
	this->dof = dof;

	this->size = size;
	this->mass = mass;

	this->startPos = pos;
	this->startDof = dof;

	cout << this->name << " initialized\n";
}

Planet::~Planet() {

}