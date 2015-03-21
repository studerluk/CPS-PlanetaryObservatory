
#include <QApplication>
#include <QMessageBox>

#include "qtview.h"
#include "qtviewctl.h"

using namespace std;


int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	SolarSystem *milky = new SolarSystem();

	QtView *gui = new QtView(milky);
	QtViewCtl *ctl = new QtViewCtl(milky, gui);

	gui->show();

	return a.exec();
}


/*
QApplication a(argc, argv);
model *m = new model();

QtGuiView *gui = new QtGuiView(m);
new QtGuiCtrl(m, gui);

//QtGuiView *guib = new QtGuiView(m);
//new QtGuiCtrl(m, guib);

gui->show();
//guib->show();
return a.exec();
*/