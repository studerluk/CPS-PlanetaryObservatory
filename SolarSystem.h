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

	void setG(double);
	mpf_class getG();

	Planet currentPlanet;

	Planet* getPlanet(int);
	void setSelectedPlanetID(int);
	int getSelectedPlanetID();

	int getFrameCount();
	int getProgBarValue();

	void setCtrlState(bool);
	bool getCtrlState();

	void tick();
	void addPlanet(string, Vector, Vector, mpf_class, mpf_class, string);
	void editPlanet(string, Vector, Vector, mpf_class, mpf_class, string);
	void deletePlanet(int);

	bool planetExists(string);
	
private:
	mpf_class G_CONST;

	Planet *planets[MAX_PLANETS];
	int selectedPlanetID;
	
	int frameCount;
	int progBarValue;

	bool ctrlsEnabled;

	void calcGravity(Planet*);

public slots:
	void resetPlanets();
	void updatePlanetColor(QString);

	void resetProgBar(int);
	void setProgBarValue(int);

	void enableCtrls();

signals:
	void errorOccured(QString);

	void ctrlStateChanged();
	void progBarChanged();

	void planetAdded(int);
	void planetDeleted(int);
	void planetChanged(int);
	void planetsReset();
	void selectionChanged();

};

#endif
