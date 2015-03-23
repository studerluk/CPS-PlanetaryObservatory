
#include "qtview.h"

using namespace std;


QtView::QtView(SolarSystem *solarSystem): QMainWindow() {
	this->solarSystem = solarSystem;

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
	SolarSystem *solSys = this->solarSystem;
	for (int i = 0; i < solSys->planetc; i++) {
		double size = solSys->planets[i]->size.get_d();
		double posx = solSys->planets[i]->pos->x.get_d();
		double posy = solSys->planets[i]->pos->y.get_d();

		this->ellipse[i] = this->scene->addEllipse(
			QRectF(posx, posy, size, size),
			QPen(Qt::SolidLine), QBrush(Qt::red));
	}

	QGraphicsEllipseItem *test = this->scene->addEllipse(
			QRectF(0, 0, 2, 2),
			QPen(Qt::SolidLine), QBrush(Qt::black));
}

void QtView::initAnimation() {
	int planetc = this->solarSystem->planetc;

	this->timer = new QTimeLine();

	for (int i = 0; i < planetc; i++) {
		this->anims[i] = new QGraphicsItemAnimation();
		this->anims[i]->setItem(this->ellipse[i]);
		this->anims[i]->setTimeLine(this->timer);
	}
}

void QtView::simulate(int count) {
	SolarSystem *solSys = this->solarSystem;
	int planetc = this->solarSystem->planetc;

	if (count *100 < 1000) {
		this->timer->setDuration(1000);
		timer->setFrameRange(0, 1000);
	} else {
		this->timer->setDuration(count *100);
		timer->setFrameRange(0, count *100);
	}

	for (int i = 0; i < count; i++) {
		solSys->tick();
		for (int j = 0; j < planetc; j++) {
			double size = solSys->planets[j]->size.get_d();
			double posx = solSys->planets[j]->pos->x.get_d();
			double posy = solSys->planets[j]->pos->y.get_d();

			double step = (double) i / count;
			this->anims[j]->setPosAt(step, QPointF(posx, posy));

			// cout << solSys->planets[j]->name << ": " << solSys->planets[j]->pos->x.get_d() << "|" << solSys->planets[j]->pos->y.get_d() << "\n";
		}
	}
	timer->start();
}
