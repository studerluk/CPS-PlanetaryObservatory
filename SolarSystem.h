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

	int getFrameCount();
	int getProgBarValue();

	void setBtnState(bool);
	bool getBtnState();

	void tick();
	void addPlanet(string, Vector, Vector, string, string);
	
private:
	mpf_class G_CONST;

	int planetc;
	Planet *planets[MAX_PLANETS];
	
	int frameCount;
	int progBarValue;

	bool btnsEnabled;

	void calcGravity(Planet*);

public slots:
	void resetPlanets();

	void resetProgBar(int);
	void updateProgBar(int);

	void enableBtns();

signals:
	void errorOccured(QString);

	void btnStateChanged();

	void progBarChanged();

	void planetsMoved();
	void planetAdded();

};

#endif
