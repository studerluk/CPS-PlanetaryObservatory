#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#define MAX_PLANETS 10

#include <QtGui>
#include <QWidget>


#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include <string>

#include "Planet.h"


using namespace std;


class SolarSystem : public QWidget {

	Q_OBJECT

public:
	SolarSystem();
	~SolarSystem();

	mpf_class getG();

	int getPlanetc();
	Planet* getPlanet(int);

	void tick();
	void addPlanet(string, Vector, Vector, string, string);
	
private:
	mpf_class G_CONST;

	int planetc;
	Planet *planets[MAX_PLANETS];
	
	void calcGravity(Planet*);

public slots:
	void resetPlanets();

signals:
	void errorOccured(QString);

	void planetsMoved();
	void planetAdded();

};

#endif
