#include "qtviewctl.h"

using namespace std;


QtViewCtl::QtViewCtl(SolarSystem *model, QtView *view) : QWidget() {
	solarSystem = model;
	gui = view;

	connect(gui->qBtnRun, SIGNAL(clicked()), this, SLOT(run()));

	gui->installEventFilter(this);
}

QtViewCtl::~QtViewCtl() {

}

void QtViewCtl::displayError() {
	QMessageBox::warning(this, "Error", "errMsg", QMessageBox::Ok);
}

void QtViewCtl::run() {
	bool ok;
	int i = (int) QInputDialog::getDouble(this, "Amoutn of ticks",
									   tr("Ticks:"), 10000, 1, 100000, 0, &ok);

	if (ok) {
		this->gui->simulate(i);
	}
}

