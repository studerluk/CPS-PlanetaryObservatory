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
#include <QMessageBox>

#include <iostream>
#include <string.h>

#include "SolarSystem.h"

using namespace std;


class QtView : public QMainWindow
{
	Q_OBJECT

public:
	QGraphicsScene *scene;
	QTimeLine *timer;

	QPushButton *qBtnAdd;
	QPushButton *qBtnEdit;
	QPushButton *qBtnDelete;
	QPushButton *qBtnReset;
	QPushButton *qBtnRun;

	QtView(SolarSystem*);
	~QtView();

	void simulate(int);

private:
	SolarSystem *model;
	
	QGraphicsEllipseItem *ellipse[MAX_PLANETS];
	QGraphicsItemAnimation *anims[MAX_PLANETS];

	void initPlanets();
	void initAnimation();
	
public slots:
	void addEllipse();

	void updateView();

	void holdButtons();
	void releaseButtons();

signals:
	void errorOccured(QString);

};

#endif // QTVIEW_H
