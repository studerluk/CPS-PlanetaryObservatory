
#include "qtview.h"

using namespace std;


QtView::QtView(SolarSystem *solarSystem): QMainWindow() {
	setWindowTitle("Solar System Simulator");

	model = solarSystem;

	// graphics
	scene = new QGraphicsScene(-100, -100, 1000, 800);
	scene->setBackgroundBrush(Qt::white);

	graphicsView = new QGraphicsView(scene);
	graphicsView->setRenderHints( QPainter::Antialiasing );
	graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
	graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);


	// control buttons
	qBtnAdd = new QPushButton("Add");
	qBtnEdit = new QPushButton("Edit");
	qBtnDelete = new QPushButton("Delete");
	qBtnReset = new QPushButton("Reset");
	qBtnRun = new QPushButton("Run");
	qBtnSetG = new QPushButton("Set G");


	// input fields
	qTxtName = new QLineEdit();
	qTxtName->setPlaceholderText("Name");
	qTxtName->setAlignment(Qt::AlignJustify);

	qTxtPosX = new QLineEdit();
	qTxtPosX->setPlaceholderText("Position X");
	qTxtPosX->setValidator(new QDoubleValidator(0, 500, 3, this));

	qTxtPosY = new QLineEdit();
	qTxtPosY->setPlaceholderText("Position Y");
	qTxtPosY->setValidator(new QDoubleValidator(0, 500, 3, this));

	qTxtDofX = new QLineEdit();
	qTxtDofX->setPlaceholderText("Dof X");
	qTxtDofX->setValidator(new QDoubleValidator(0, 500, 3, this));

	qTxtDofY = new QLineEdit();
	qTxtDofY->setPlaceholderText("Dof Y");
	qTxtDofY->setValidator(new QDoubleValidator(0, 500, 3, this));

	qTxtMass = new QLineEdit();
	qTxtMass->setPlaceholderText("Mass");
	qTxtMass->setValidator(new QDoubleValidator(0, 1000000, 3, this));

	qTxtSize = new QLineEdit();
	qTxtSize->setPlaceholderText("Size");
	qTxtSize->setValidator(new QDoubleValidator(0, 200, 3, this));

	progBar = new QProgressBar(this);
	progBar->setMinimum(0);
	progBar->setMaximum(1);
	progBar->setValue(0);

	// building ctrl layout
	QGridLayout *loutCtrl = new QGridLayout();
	loutCtrl->addWidget(qBtnAdd, 0, 0, 1, 2, Qt::AlignJustify);
	loutCtrl->addWidget(qBtnEdit, 1, 0, 1, 2, Qt::AlignJustify);
	loutCtrl->addWidget(qBtnDelete, 2, 0, 1, 2, Qt::AlignJustify);
	loutCtrl->addWidget(qBtnSetG, 3, 0, 1, 2, Qt::AlignJustify);
	loutCtrl->addWidget(qBtnRun, 4, 0, 1, 2, Qt::AlignJustify);
	loutCtrl->addWidget(qBtnReset, 5, 0, 1, 2, Qt::AlignJustify);

	loutCtrl->addWidget(qTxtName, 6, 0, 1, 2, Qt::AlignJustify);
	loutCtrl->addWidget(qTxtPosX, 7, 0, 1, 1, Qt::AlignJustify);
	loutCtrl->addWidget(qTxtPosY, 7, 1, 1, 1, Qt::AlignJustify);
	loutCtrl->addWidget(qTxtDofX, 8, 0, 1, 1, Qt::AlignJustify);
	loutCtrl->addWidget(qTxtDofY, 8, 1, 1, 1, Qt::AlignJustify);
	loutCtrl->addWidget(qTxtMass, 9, 0, 1, 2, Qt::AlignJustify);
	loutCtrl->addWidget(qTxtSize, 10, 0, 1, 2, Qt::AlignJustify);

	loutCtrl->addWidget(progBar, 11, 0, 1, 2, Qt::AlignJustify);

	// Misc
	QDockWidget *dock = new QDockWidget("Controlls", this);
	dock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	dock->setWidget(new QWidget());
	dock->widget()->setLayout(loutCtrl);

	addDockWidget(Qt::RightDockWidgetArea, dock);
	setCentralWidget(graphicsView);

	initPlanets();
	initAnimation();
}

QtView::~QtView() {

}

void QtView::initPlanets() {
	for (int i = 0; i < model->getPlanetc(); i++) {
		double size = model->getPlanet(i)->size.get_d();
		double posx = model->getPlanet(i)->pos.x.get_d();
		double posy = model->getPlanet(i)->pos.y.get_d();

		ellipse[i] = scene->addEllipse(QRectF(posx, posy, size, size),
			QPen(Qt::SolidLine), QBrush(Qt::red));
		ellipse[i]->setFlag(QGraphicsItem::ItemIsSelectable, true);
	}

	QGraphicsEllipseItem *test = scene->addEllipse(
			QRectF(0, 0, 2, 2),
			QPen(Qt::SolidLine), QBrush(Qt::black));
}

void QtView::initAnimation() {
	timer = new QTimeLine();

	for (int i = 0; i < model->getPlanetc(); i++) {
		anims[i] = new QGraphicsItemAnimation();
		anims[i]->setItem(ellipse[i]);
		anims[i]->setTimeLine(timer);
	}
}

void QtView::simulate(int count) {
	model->setCtrlState(false);

	int duration = 1000;
	if (count *100 > 1000)
		duration = count *100;

	timer->setDuration(duration);
	timer->setFrameRange(0, duration);

	model->resetProgBar(duration);

	for (int i = 0; i < count; i++) {
		model->tick();
		model->updateProgBar(i);
		for (int j = 0; j < model->getPlanetc(); j++) {
			double size = model->getPlanet(j)->size.get_d();
			double posx = model->getPlanet(j)->pos.x.get_d();
			double posy = model->getPlanet(j)->pos.y.get_d();

			double step = (double) i / count;
			anims[j]->setPosAt(step, QPointF(posx, posy));
		}
	}
	timer->start();
}

void QtView::addEllipse() {
	int i = model->getPlanetc() -1;

	double size = model->getPlanet(i)->size.get_d();
	double posx = model->getPlanet(i)->pos.x.get_d();
	double posy = model->getPlanet(i)->pos.y.get_d();

	ellipse[i] = scene->addEllipse(QRectF(posx, posy, size, size),
			QPen(Qt::SolidLine), QBrush(Qt::red));
	ellipse[i]->setFlag(QGraphicsItem::ItemIsSelectable, true);

	anims[i] = new QGraphicsItemAnimation();
	anims[i]->setItem(ellipse[i]);
	anims[i]->setTimeLine(timer);

	this->updateView();
}

void QtView::updateView() {
	for (int i = 0; i < model->getPlanetc(); i++) {
		double posx = model->getPlanet(i)->pos.x.get_d();
		double posy = model->getPlanet(i)->pos.y.get_d();

		ellipse[i]->setPos(QPointF(posx, posy));
	}
}

void QtView::updateCtrls() {
	bool state = model->getCtrlState();

	qBtnAdd->setEnabled(state);
	qBtnEdit->setEnabled(state);
	qBtnDelete->setEnabled(state);
	qBtnRun->setEnabled(state);
	qBtnSetG->setEnabled(state);

	qTxtName->setEnabled(state);
	qTxtPosX->setEnabled(state);
	qTxtPosY->setEnabled(state);
	qTxtDofX->setEnabled(state);
	qTxtDofY->setEnabled(state);
	qTxtMass->setEnabled(state);
	qTxtSize->setEnabled(state);
}

void QtView::updateProgBar() {
	int frameCount = model->getFrameCount();

	if (progBar->maximum() != frameCount)
		progBar->setMaximum(frameCount);

	progBar->setValue(model->getProgBarValue());
}

void QtView::updateSelection() {
	Planet *planet = model->getSelectedPlanet();

	qTxtName->setText(QString::fromStdString(planet->name));
	qTxtPosX->setText(QString::number(planet->pos.x.get_d(), 'f', 3));
	qTxtPosY->setText(QString::number(planet->pos.y.get_d(), 'f', 3));
	qTxtDofX->setText(QString::number(planet->dof.x.get_d(), 'f', 3));
	qTxtDofY->setText(QString::number(planet->dof.y.get_d(), 'f', 3));
	qTxtMass->setText(QString::number(planet->mass.get_d(), 'f', 3));
	qTxtSize->setText(QString::number(planet->size.get_d(), 'f', 3));
}

QGraphicsEllipseItem* QtView::getEllipse(int i) {
	return ellipse[i];
}
