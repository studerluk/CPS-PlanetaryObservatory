#ifndef COORDS_H
#define COORDS_H

#define MPF_SIZE 512

#include <gmp.h>
#include <gmpxx.h>
#include <string>

using namespace std;


class Vector {

public:
	Vector();
	Vector(string, string);
	Vector(mpf_class, mpf_class);
	~Vector(void);

	void set(string, string);
	void set(mpf_class, mpf_class);

	void add(Vector&);
	void sub(Vector&);

	mpf_class x;
	mpf_class y;

};

#endif