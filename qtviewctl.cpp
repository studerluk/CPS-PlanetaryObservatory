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
	connect(view->scene, SIGNAL(selectionChanged()), this, SLOT(selectionChanged()));
	connect(view->qCBoxColor, SIGNAL(currentTextChanged(QString)), model, SLOT(updatePlanetColor(QString)));

	connect(view->timer, SIGNAL(finished()), model, SLOT(enableCtrls()));
	// connect(view->timer, SIGNAL(finished()), view, SLOT(updateView()));
	connect(view->timer, SIGNAL(frameChanged(int)), model, SLOT(updateProgBar(int)));
	connect(view->timer, SIGNAL(frameChanged(int)), view, SLOT(updateAnimInfo()));

	connect(model, SIGNAL(planetAdded(int)), view, SLOT(addEllipse(int)));
	connect(model, SIGNAL(planetDeleted(int)), view, SLOT(delEllipse(int)));
	connect(model, SIGNAL(planetsMoved()), view, SLOT(updateView()));
	connect(model, SIGNAL(progBarChanged()), view, SLOT(updateAnimInfo()));
	connect(model, SIGNAL(ctrlStateChanged()), view, SLOT(updateCtrls()));
	connect(model, SIGNAL(selectionChanged()), view, SLOT(updateAnimInfo()));
	

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

	if (ok) view->animate(i);
}

void QtViewCtl::addPlanet() {
	Planet *planet = extractPlanet();

	if (planet != NULL) {
		if (model->planetExists(planet->name)) {
			QMessageBox::warning(this, "Error", "Planet already exists", QMessageBox::Ok);
		} else {
			model->addPlanet(planet->name, planet->pos, planet->dof, planet->mass, planet->size, planet->color);
			QMessageBox::information(this, "Success", "Planet updated", QMessageBox::Ok);
		}
	}
}

void QtViewCtl::editPlanet() {
	Planet *planet = extractPlanet();
	
	if (planet != NULL) {
		if (!model->planetExists(planet->name)) {
			QMessageBox::warning(this, "Error", "Planet does not exists", QMessageBox::Ok);
		} else {
			model->editPlanet(planet->name, planet->pos, planet->dof, planet->mass, planet->size, planet->color);
			QMessageBox::information(this, "Success", "Planet updated", QMessageBox::Ok);
		}
	}
}

Planet* QtViewCtl::extractPlanet() {
	QString name = view->qTxtName->text();
	QString posx = view->qTxtPosX->text();
	QString posy = view->qTxtPosY->text();
	QString dofx = view->qTxtDofX->text();
	QString dofy = view->qTxtDofY->text();
	QString mass = view->qTxtMass->text();
	QString size = view->qTxtSize->text();
	QString color = view->qCBoxColor->currentText();

	if (name.isEmpty() || posx.isEmpty() || posy.isEmpty() || dofx.isEmpty() || dofy.isEmpty() || mass.isEmpty() || size.isEmpty()) {
		QMessageBox::warning(this, "Error", "Every field has to fild out", QMessageBox::Ok);
		return NULL;
	} else {
		return new Planet(name.toStdString(), posx.toStdString(), posy.toStdString(),
				dofx.toStdString(), dofy.toStdString(), mass.toStdString(), size.toStdString(), color.toStdString());
	}
}

void QtViewCtl::delPlanet() {
	int id = model->getSelectedPlanetID();
	model->deletePlanet(id);
}

void QtViewCtl::resetPlanets() {
	if (view->timer->state() == QTimeLine::Running)
		view->timer->stop();

	model->enableCtrls();
	model->resetPlanets();
	model->resetProgBar(100);
}

void QtViewCtl::selectionChanged() {
	if (!view->scene->selectedItems().isEmpty()) {
		QGraphicsItem *focused = view->scene->selectedItems().first();

		for (int i = 0; i < MAX_PLANETS; i++) {
			if (model->getPlanet(i) != NULL) {
				QGraphicsItem *ellipse = view->getEllipse(i);

				if (focused == ellipse) {
					model->setSelectedPlanetID(i);
					i = MAX_PLANETS;
				}
			}
		}
	} else {
		model->setSelectedPlanetID(-1);
	}
}

void QtViewCtl::setG() {
	bool ok;
	double g = QInputDialog::getDouble(this, "Set gravity constant", "Ticks:", model->getG().get_d(), 0.0000001, 1, 7, &ok);

	if (ok) model->setG(g);
}