#ifndef QTVIEW_H
#define QTVIEW_H

#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QApplication>
#include <QtGui>
#include <QWidget>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QTimeLine>
#include <QGraphicsItemAnimation>

#include "SolarSystem.h"

using namespace std;


class QtView : public QMainWindow
{
	Q_OBJECT

public:
	QGraphicsScene *scene;
	QPushButton *qBtnAdd;
	QPushButton *qBtnEdit;
	QPushButton *qBtnDelete;
	QPushButton *qBtnReset;
	QPushButton *qBtnRun;

	QtView(SolarSystem*);
	~QtView();

	void movePlanets();


private:
	SolarSystem *solarSystem;
	QGraphicsEllipseItem *ellipse[10];

	void initPlanets();
};

#endif // QTVIEW_H
