#include "Coords.h"

using namespace std;


Coords::Coords(string x, string y) {
	this->x = mpf_class(x, 512);
	this->y = mpf_class(y, 512);
}

Coords::~Coords() {

}

