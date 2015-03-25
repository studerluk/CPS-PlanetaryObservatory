#include "qtviewctl.h"

#include <iostream>

using namespace std;


QtViewCtl::QtViewCtl(SolarSystem *solarSystem, QtView *gui) : QWidget() {
	model = solarSystem;
	view = gui;

	connect(view->qBtnRun, SIGNAL(clicked()), this, SLOT(run()));
	connect(view->qBtnReset, SIGNAL(clicked()), this, SLOT(reset()));
	connect(view->timer, SIGNAL(finished()), this, SLOT(enableBtns()));
	connect(view->qBtnAdd, SIGNAL(clicked()), this, SLOT(addPlanet()));

	view->installEventFilter(this);

	// cout << solarSystem->planets[0]->name;
	//gui->updateView();
}

QtViewCtl::~QtViewCtl() {

}

void QtViewCtl::displayError() {
	QMessageBox::warning(this, "Error", "errMsg", QMessageBox::Ok);
}

void QtViewCtl::run() {
	bool ok;
	int i = (int) QInputDialog::getDouble(this, "Amoutn of ticks",
									   tr("Ticks:"), 10000, 1, 100000, 0, &ok);

	if (ok) view->simulate(i);
}

void QtViewCtl::reset() {
	model->resetPlanets();
	view->updateView();
}

void QtViewCtl::addPlanet() {
	model->addPlanet("sun\0", Vector("0", "0"), Vector("0", "0"), "1000000", "100");
	cout << model->getPlanetc();
	view->updateView();
}

void QtViewCtl::editPlanet() {
	
}

void QtViewCtl::delPlanet() {
	
}

void QtViewCtl::enableBtns() {
	view->qBtnAdd->setEnabled(true);
	view->qBtnEdit->setEnabled(true);
	view->qBtnDelete->setEnabled(true);
	view->qBtnReset->setEnabled(true);
	view->qBtnRun->setEnabled(true);
}