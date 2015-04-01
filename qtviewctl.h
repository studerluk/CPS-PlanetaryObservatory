#ifndef QTVIEWCTL_H
#define QTVIEWCTL_H

#include <QMainWindow>
#include <QWidget>
#include <QtGui>
#include <QApplication>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>
#include <QString>

#include "Planet.h"
#include "SolarSystem.h"
#include "qtview.h"

using namespace std;


class QtViewCtl: public QWidget {

	Q_OBJECT

public:
	QtViewCtl(SolarSystem*, QtView*);
	~QtViewCtl();

private:
	SolarSystem *model;
	QtView *view;

	Planet* extractPlanet();

public slots:
	void displayError(QString);

	void run();
	void addPlanet();
	void editPlanet();
	void delPlanet();
	void setG();

	void resetPlanets();

	void selectionChanged();

};

#endif // QTVIEWCTL_H
