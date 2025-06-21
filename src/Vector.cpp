#include "Vector.h"

using namespace std;

Vector::Vector() {

}

Vector::Vector(string s_x, string s_y) {
	this->x = mpf_class(s_x, MPF_SIZE);
	this->y = mpf_class(s_y, MPF_SIZE);
}

Vector::Vector(mpf_class x, mpf_class y) {
	this->x = x;
	this->y = y;
}

Vector::~Vector(void) {

}

void Vector::set(string x, string y) {
	this->x = mpf_class(x, MPF_SIZE);
	this->y = mpf_class(y, MPF_SIZE);
}

void Vector::set(mpf_class x, mpf_class y) {
	this->x = x;
	this->y = y;
}

void Vector::add(Vector &v) {
	x += v.x;
	y += v.x;
}

void Vector::sub(Vector &v) {
	x -= v.x;
	y -= v.x;
}
