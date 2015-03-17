#include "qtview.h"
#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	QtView *gui = new QtView();
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