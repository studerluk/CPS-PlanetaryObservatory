
#include "qtview.h"

using namespace std;


QtView::QtView(SolarSystem *solarSystem): QMainWindow() {
	model = solarSystem;

	// graphics
	scene = new QGraphicsScene(-100, -100, 1000, 800);
	scene->setBackgroundBrush(Qt::white);

	QGraphicsView *graph = new QGraphicsView(scene);
	graph->setRenderHints( QPainter::Antialiasing );
	graph->setDragMode(QGraphicsView::ScrollHandDrag);
	graph->setResizeAnchor(QGraphicsView::AnchorViewCenter);


	// control buttons
	qBtnAdd = new QPushButton("Add");
	qBtnEdit = new QPushButton("Edit");
	qBtnDelete = new QPushButton("Delete");
	qBtnReset = new QPushButton("Reset");
	qBtnRun = new QPushButton("Run");

	QVBoxLayout *lout_btns = new QVBoxLayout(); // Layout
	lout_btns->addWidget(qBtnAdd);
	lout_btns->addWidget(qBtnEdit);
	lout_btns->addWidget(qBtnDelete);
	lout_btns->addWidget(qBtnReset);
	lout_btns->addWidget(qBtnRun);


	// building window
	QDockWidget *dock = new QDockWidget("Controlls", this);
	dock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	dock->setWidget(new QWidget());
	dock->widget()->setLayout(lout_btns);

	this->addDockWidget(Qt::RightDockWidgetArea, dock);
	this->setCentralWidget(graph);

	progBar = new QProgressBar(this);
	progBar->setMinimum(0);
	progBar->setMaximum(1);
	progBar->setValue(0);
	lout_btns->addWidget(progBar);

	this->initPlanets();
	this->initAnimation();
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
	model->setBtnState(false);

	int duration = 1000;
	if (count *100 > 1000)
		duration = count *100;

	timer->setDuration(duration);
	timer->setFrameRange(0, duration);

	model->resetProgBar(duration);

	for (int i = 0; i < count; i++) {
		model->tick();
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

void QtView::updateBtns() {
	bool state = model->getBtnState();

	qBtnAdd->setEnabled(state);
	qBtnEdit->setEnabled(state);
	qBtnDelete->setEnabled(state);
	qBtnReset->setEnabled(state);
	qBtnRun->setEnabled(state);
}

void QtView::updateProgBar() {
	int frameCount = model->getFrameCount();
	int progBarValue = model->getProgBarValue();

	if (progBar->maximum() != frameCount)
		progBar->setMaximum(model->getFrameCount());

	if (progBar->value() != progBarValue)
		progBar->setValue(model->getProgBarValue());
}
