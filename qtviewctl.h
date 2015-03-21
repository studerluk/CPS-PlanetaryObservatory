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

#include "SolarSystem.h"
#include "qtview.h"

using namespace std;


class QtViewCtl: public QWidget {

    Q_OBJECT

public:
    QtViewCtl(SolarSystem*, QtView*);
    ~QtViewCtl();

private:
    SolarSystem *solarSystem;
    QtView *gui;

public slots:
	void run();
    void displayError();

// 	void changeQry(QString);
// 	void updateQry();

};

#endif // QTVIEWCTL_H
