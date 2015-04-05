#ifndef QTVIEW_H
#define QTVIEW_H

#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QApplication>
#include <QtGui>
#include <QWidget>
#include <QPushButton>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QMessageBox>
#include <QDockWidget>
#include <QProgressBar>
#include <QLineEdit>
#include <QComboBox>

#include <iostream>
#include <string.h>

#include "SolarSystem.h"
#include "Planet.h"

using namespace std;


class QtView : public QMainWindow
{
	Q_OBJECT

public:
	QGraphicsScene *scene;
	QTimeLine *timer;

	QPushButton *qBtnAdd, *qBtnEdit, *qBtnDelete, *qBtnReset, *qBtnRun, *qBtnSetG;
	QLineEdit *qTxtName, *qTxtPosX, *qTxtPosY, *qTxtDofX, *qTxtDofY, *qTxtMass, *qTxtSize;
	QComboBox *qCBoxColor;

	QtView(SolarSystem*);
	~QtView();

	void animate(int);

private:
	SolarSystem *model;

	QGraphicsView *graphicsView;	
	QGraphicsEllipseItem *ellipse[MAX_PLANETS];
	QGraphicsItemAnimation *anims[MAX_PLANETS];

	QProgressBar *progBar;

	QColor translateColor(string);

public slots:
	void addEllipse(int);
	void delEllipse(int);

	void updateView();
	void updateAnimInfo();
	void updateCtrls();
	void updateSelection();

signals:
	void errorOccured(QString);

};

#endif // QTVIEW_H
