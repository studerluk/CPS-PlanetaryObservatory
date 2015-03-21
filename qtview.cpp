
#include "qtview.h"

using namespace std;


QtView::QtView(SolarSystem *solarSystem): QMainWindow() {
	this->solarSystem = solarSystem;

	// graphics
	scene = new QGraphicsScene(-100, -100, 1000, 800);
	scene->setBackgroundBrush(Qt::black);

	QGraphicsView *graph = new QGraphicsView(scene);
	graph->setRenderHints( QPainter::Antialiasing );


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
}

QtView::~QtView() {

}

// planets are not centered...
void QtView::initPlanets() {
	SolarSystem *solSys = this->solarSystem;
	for (int i = 0; i < solSys->planetc; i++)
		this->ellipse[i] = this->scene->addEllipse(
			QRectF(0, 0, solSys->planets[i]->size.get_d(), solSys->planets[i]->size.get_d()),
			QPen(Qt::SolidLine), QBrush(Qt::red));
}

void QtView::movePlanets() {
	SolarSystem *solSys = this->solarSystem;
	for (int i = 0; i < solSys->planetc; i++)
		this->ellipse[i]->setPos(solSys->planets[i]->pos->x.get_d(),
									solSys->planets[i]->pos->y.get_d());
}

// Try to fix with this...

// void QtView::simulate(int count) {
// 	SolarSystem *solSys = this->solarSystem;

// 	QTimeLine *timer = new QTimeLine(5000);
// 	timer->setFrameRange(0, 100);

// 	QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
// 	// for (int i = 0; i < this->solarSystem->planetc; i++)
// 	// 	animation->setItem(this->ellipse[i]);
// 	animation->setItem(this->ellipse[0]);
// 	animation->setTimeLine(timer);

// 	for (int i = 0; i < count; ++i) {
// 		this->solarSystem->tick();
// 		animation->setPosAt(i / count,
// 			QPointF(solSys->planets[i]->pos->x.get_d(),
// 			solSys->planets[i]->pos->y.get_d()));
// 	}

// 	timer->start();
// }

// ===================================================================


// QGraphicsItem *ball = new QGraphicsEllipseItem(0, 0, 20, 20);

// QTimeLine *timer = new QTimeLine(5000);
// timer->setFrameRange(0, 100);

// QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
// animation->setItem(ball);
// animation->setTimeLine(timer);

// for (int i = 0; i < 200; ++i)
// 	animation->setPosAt(i / 200.0, QPointF(i, i));

// QGraphicsScene *scene = new QGraphicsScene();
// scene->setSceneRect(0, 0, 250, 250);
// scene->addItem(ball);

// QGraphicsView *view = new QGraphicsView(scene);
// view->show();

// timer->start();



	// QPropertyAnimation anim = QPropertyAnimation(this, "pos");

// 	SolarSystem *solSys = this->solarSystem;
// 	for (int i = 0; i < solSys->planetc; i++) {

// 		QPropertyAnimation* anim = new QPropertyAnimation(this->ellipse[i], "pos");

// 		// anim.setTargetObject(this->ellipse[i]);

// 		anim->setDuration(2000);
// 		anim->setStartValue(this->ellipse[i]->pos());
// 		anim->setEndValue(QPointF(solSys->planets[i]->pos->x.get_d(),
// 									solSys->planets[i]->pos->y.get_d()));
// 		anim->setEasingCurve(QEasingCurve::InOutElastic);

// 		// Listen animation finished signal
// 		//QObject::connect(anim, SIGNAL(finished()), this, SLOT(animationFinished()));

// 		// Start animation and delete QPropertyAnimation class on the end
// 		anim->start(QAbstractAnimation::DeleteWhenStopped);




		// this->planets[i]->setPos(solSys->planets[i]->pos->x.get_d(),
		// 							solSys->planets[i]->pos->y.get_d());

		// free(anim);
// 	}
// }


// ain't much of an animation yet, following could sort this out...

// void PictureItem::animatePosition(const QPointF& start, const QPointF& end)
// {
// 	// Start animate this class
// 	QPropertyAnimation* anim = new QPropertyAnimation(this, "pos");

// 	// 2 second duration animation
// 	anim->setDuration(2000);
// 	// position to start animation
// 	anim->setStartValue(start);
// 	// end position of animation
// 	anim->setEndValue(end);
// 	// easing curve
// 	anim->setEasingCurve(QEasingCurve::InOutElastic);

// 	// Listen animation finished signal
// 	QObject::connect(anim, SIGNAL(finished()), this, SLOT(animationFinished()));

// 	// Start animation and delete QPropertyAnimation class on the end
// 	anim->start(QAbstractAnimation::DeleteWhenStopped);
// }

// QParallelAnimationGroup *group = new QParallelAnimationGroup;
// group->addAnimation(anim1);
// group->addAnimation(anim2);

// group->start();


// or maybe this one...

// QGraphicsItem *ball = new QGraphicsEllipseItem(0, 0, 20, 20);

// QTimeLine *timer = new QTimeLine(5000);
// timer->setFrameRange(0, 100);

// QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
// animation->setItem(ball);
// animation->setTimeLine(timer);

// for (int i = 0; i < 200; ++i)
// 	animation->setPosAt(i / 200.0, QPointF(i, i));

// QGraphicsScene *scene = new QGraphicsScene();
// scene->setSceneRect(0, 0, 250, 250);
// scene->addItem(ball);

// QGraphicsView *view = new QGraphicsView(scene);
// view->show();

// timer->start();
