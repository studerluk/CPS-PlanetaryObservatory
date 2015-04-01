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
	void setG(double);

	Planet* getPlanet(int);
	void setSelectedPlanet(Planet*);
	Planet* getSelectedPlanet();
	void setSelectedPlanetID(int);
	int getSelectedPlanetID();

	int getFrameCount();
	int getProgBarValue();

	void setCtrlState(bool);
	bool getCtrlState();

	void tick();
	void addPlanet(string, Vector, Vector, string, string);
	void addPlanet(QString, QString, QString, QString, QString, QString, QString);
	void editPlanet(string, Vector, Vector, string, string);
	void editPlanet(QString, QString, QString, QString, QString, QString, QString);
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

	void resetProgBar(int);
	void updateProgBar(int);

	void enableCtrls();

signals:
	void errorOccured(QString);

	void ctrlStateChanged();

	void progBarChanged();

	void planetsMoved();
	void planetAdded(int);
	void planetDeleted(int);
	void selectionChanged();

};

#endif
