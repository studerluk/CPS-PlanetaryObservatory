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
	int planetc;
	
	SolarSystem();
	virtual ~SolarSystem();

	void tick();
	Planet *planets[10];

private:
	mpf_class G_CONST;

	void movePlanet(Planet*);
	void calcGravity(Planet*);

// public slots:
// 	void search(QString, QString);
// 	void errHandling(int);

// signals:
// 	void queryChanged();
// 	void searchDone();
// 	void indexChanged();
// 	void idChanged();
// 	void selectionChanged();
// 	void mgntSelChanged();
// 	void wordlistChanged();
// 	void mgntViewOpened();
// 	void catChanged();
// 	void headChanged();
// 	void errorOccurred(QString);

};

#endif
