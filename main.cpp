
#include <QApplication>
#include <QMessageBox>

#include "qtview.h"
#include "qtviewctl.h"

#include "SolarSystem.h"

using namespace std;


int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	SolarSystem *milky = new SolarSystem();

	QtView *gui = new QtView(milky);
	QtViewCtl *ctl = new QtViewCtl(milky, gui);

	// QtView *gui2 = new QtView(milky);
	// QtViewCtl *ctl2 = new QtViewCtl(milky, gui2);

	gui->show();
	// gui2->show();

	return a.exec();
}
