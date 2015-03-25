
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

	QHBoxLayout *lout_btns = new QHBoxLayout(); // Layout
	lout_btns->addWidget(qBtnAdd);
	lout_btns->addWidget(qBtnEdit);
	lout_btns->addWidget(qBtnDelete);
	lout_btns->addWidget(qBtnReset);
	lout_btns->addWidget(qBtnRun);


	// building window
	QVBoxLayout *lout_main = new QVBoxLayout();
	lout_main->addWidget(graph);
	lout_main->addLayout(lout_btns);

	QWidget *widget = new QWidget();
	widget->setLayout(lout_main);

	this->setCentralWidget(widget);

	this->initPlanets();
	this->initAnimation();
}

QtView::~QtView() {

}

// planets are not centered...
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
	this->holdButtons();

	if (count *100 < 1000) {
		timer->setDuration(1000);
		timer->setFrameRange(0, 1000);
	} else {
		timer->setDuration(count *100);
		timer->setFrameRange(0, count *100);
	}

	for (int i = 0; i < count; i++) {
		model->tick();
		for (int j = 0; j < model->getPlanetc(); j++) {
			double size = model->getPlanet(j)->size.get_d();
			double posx = model->getPlanet(j)->pos.x.get_d();
			double posy = model->getPlanet(j)->pos.y.get_d();

			double step = (double) i / count;
			anims[j]->setPosAt(step, QPointF(posx, posy));

			// cout << solSys->planets[j]->name << ": " << solSys->planets[j]->pos->x.get_d() << "|" << solSys->planets[j]->pos->y.get_d() << "\n";
		}
	}
	timer->start();
}

void QtView::updateView() {
	for (int i = 0; i < model->getPlanetc(); i++) {
		double posx = model->getPlanet(i)->pos.x.get_d();
		double posy = model->getPlanet(i)->pos.y.get_d();

		ellipse[i]->setPos(QPointF(posx, posy));
	}
}

void QtView::holdButtons() {
	qBtnAdd->setEnabled(false);
	qBtnEdit->setEnabled(false);
	qBtnDelete->setEnabled(false);
	qBtnReset->setEnabled(false);
	qBtnRun->setEnabled(false);
}

void QtView::releaseButtons() {

}
