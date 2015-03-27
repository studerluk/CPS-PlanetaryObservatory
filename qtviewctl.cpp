#include "qtviewctl.h"

#include <iostream>

using namespace std;


QtViewCtl::QtViewCtl(SolarSystem *solarSystem, QtView *gui) : QWidget() {
	model = solarSystem;
	view = gui;

	connect(model, SIGNAL(errorOccured(QString)), this, SLOT(displayError(QString)));
	connect(view, SIGNAL(errorOccured(QString)), this, SLOT(displayError(QString)));

	connect(view->qBtnRun, SIGNAL(clicked()), this, SLOT(run()));
	connect(view->qBtnReset, SIGNAL(clicked()), model, SLOT(resetPlanets()));
	connect(view->qBtnAdd, SIGNAL(clicked()), this, SLOT(addPlanet()));
	connect(view->timer, SIGNAL(finished()), view, SLOT(releaseButtons()));

	connect(model, SIGNAL(planetAdded()), view, SLOT(addEllipse()));
	connect(model, SIGNAL(planetsMoved()), view, SLOT(updateView()));
	

	view->installEventFilter(this);

	// cout << solarSystem->planets[0]->name;
	//gui->updateView();
}

QtViewCtl::~QtViewCtl() {

}

void QtViewCtl::displayError(QString errMsg) {
	QMessageBox::warning(this, "Error", errMsg, QMessageBox::Ok);
}

void QtViewCtl::run() {
	bool ok;
	int i = (int) QInputDialog::getDouble(this, "Amoutn of ticks", "Ticks:", 100, 1, 100000, 0, &ok);

	if (ok) view->simulate(i);
}

void QtViewCtl::addPlanet() {
	model->addPlanet("sun\0", Vector("50", "50"), Vector("0", "0"), "1000000", "100");
}

void QtViewCtl::editPlanet() {
	
}

void QtViewCtl::delPlanet() {
	
}

