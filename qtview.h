#ifndef QTVIEW_H
#define QTVIEW_H

#define MAX_PLANETS 10
#define ANIM_SPEED 0.9

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
#include <iostream>

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

	void simulate(int);


private:
	SolarSystem *solarSystem;
	QGraphicsEllipseItem *ellipse[MAX_PLANETS];

	QTimeLine *timer;
	QGraphicsItemAnimation *anims[MAX_PLANETS];

	void initPlanets();
	void initAnimation();
};

#endif // QTVIEW_H
