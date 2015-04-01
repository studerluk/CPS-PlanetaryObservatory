#include "qtviewctl.h"

#include <iostream>

using namespace std;


QtViewCtl::QtViewCtl(SolarSystem *solarSystem, QtView *gui) : QWidget() {
	model = solarSystem;
	view = gui;

	connect(model, SIGNAL(errorOccured(QString)), this, SLOT(displayError(QString)));
	connect(view, SIGNAL(errorOccured(QString)), this, SLOT(displayError(QString)));

	connect(view->qBtnRun, SIGNAL(clicked()), this, SLOT(run()));
	connect(view->qBtnReset, SIGNAL(clicked()), this, SLOT(resetPlanets()));
	connect(view->qBtnAdd, SIGNAL(clicked()), this, SLOT(addPlanet()));
	connect(view->qBtnEdit, SIGNAL(clicked()), this, SLOT(editPlanet()));
	connect(view->qBtnDelete, SIGNAL(clicked()), this, SLOT(delPlanet()));
	connect(view->qBtnSetG, SIGNAL(clicked()), this, SLOT(setG()));
	connect(view->timer, SIGNAL(finished()), model, SLOT(enableCtrls()));
	connect(view->timer, SIGNAL(frameChanged(int)), model, SLOT(updateProgBar(int)));
	connect(view->scene, SIGNAL(selectionChanged()), this, SLOT(selectionChanged()));

	connect(model, SIGNAL(planetAdded()), view, SLOT(addEllipse()));
	connect(model, SIGNAL(planetsMoved()), view, SLOT(updateView()));
	connect(model, SIGNAL(progBarChanged()), view, SLOT(updateProgBar()));
	connect(model, SIGNAL(ctrlStateChanged()), view, SLOT(updateCtrls()));
	connect(model, SIGNAL(selectionChanged()), view, SLOT(updateSelection()));
	

	view->installEventFilter(this);
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
	QString name = view->qTxtName->text();
	QString posx = view->qTxtPosX->text();
	QString posy = view->qTxtPosY->text();
	QString dofx = view->qTxtDofX->text();
	QString dofy = view->qTxtDofY->text();
	QString mass = view->qTxtMass->text();
	QString size = view->qTxtSize->text();

	if (name.isEmpty() || posx.isEmpty() || posy.isEmpty() || dofx.isEmpty() || dofy.isEmpty() || mass.isEmpty() || size.isEmpty()) {
			QMessageBox::warning(this, "Error", "Every field has to fild out", QMessageBox::Ok);
	} else {
		if (model->planetExists(name.toUtf8().constData())) {
			QMessageBox::warning(this, "Error", "Planet already exists", QMessageBox::Ok);
		} else {
			model->addPlanet(name, posx, posy, dofx, dofy, mass, size);
		}
	}
}

void QtViewCtl::editPlanet() {
	QString name = view->qTxtName->text();
	QString posx = view->qTxtPosX->text();
	QString posy = view->qTxtPosY->text();
	QString dofx = view->qTxtDofX->text();
	QString dofy = view->qTxtDofY->text();
	QString mass = view->qTxtMass->text();
	QString size = view->qTxtSize->text();

	if (name.isEmpty() || posx.isEmpty() || posy.isEmpty() || dofx.isEmpty() || dofy.isEmpty() || mass.isEmpty() || size.isEmpty()) {
			QMessageBox::warning(this, "Error", "Every field has to fild out", QMessageBox::Ok);
	} else {
		if (!model->planetExists(name.toUtf8().constData())) {
			QMessageBox::warning(this, "Error", "Planet does not exists", QMessageBox::Ok);
		} else {
			model->editPlanet(name, posx, posy, dofx, dofy, mass, size);
			QMessageBox::warning(this, "Error", "Planet updated", QMessageBox::Ok);
		}
	}
}

void QtViewCtl::delPlanet() {
	
}

void QtViewCtl::resetPlanets() {
	if (view->timer->state() == QTimeLine::Running)
		view->timer->stop();

	model->enableCtrls();
	model->resetPlanets();
	model->resetProgBar(100);
}

void QtViewCtl::selectionChanged() {
	Planet *selectedPlanet = getSelectedPlanet();
	model->setSelectedPlanet(selectedPlanet);
}

Planet* QtViewCtl::getSelectedPlanet() {
	if (!view->scene->selectedItems().isEmpty()) {
		QGraphicsItem *focused = view->scene->selectedItems().first();

		for (int i = 0; i < model->getPlanetc(); i++) {
			QGraphicsItem *ellipse = view->getEllipse(i);

			if (focused == ellipse)
				return model->getPlanet(i);
		}
	}
}

void QtViewCtl::setG() {
	bool ok;
	double g = QInputDialog::getDouble(this, "Set gravity constant", "Ticks:", 0.0001, 0.0000001, 1, 7, &ok);

	if (ok) model->setG(g);
}