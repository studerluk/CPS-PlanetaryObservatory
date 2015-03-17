#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QApplication>
#include <QtGui>
#include <QWidget>
#include <QPushButton>

#include "qtview.h"

QtView::QtView(): QMainWindow() {

	// window options
	QGraphicsScene *scene = new QGraphicsScene;
	scene->setSceneRect(-100, -100, 1000, 800);
	scene->setBackgroundBrush(Qt::black);

	QGraphicsEllipseItem *item = scene->addEllipse(QRectF(100, 100, 50, 50), QPen(Qt::SolidLine), QBrush(Qt::red));


	QGraphicsView *graph = new QGraphicsView(scene);
	graph->setRenderHints( QPainter::Antialiasing );

	item->moveBy(50,50);

	QPushButton *btn_add = new QPushButton("Add");
	QPushButton *btn_edit = new QPushButton("Edit");
	QPushButton *btn_delete = new QPushButton("Delete");


	QVBoxLayout *lout_main = new QVBoxLayout();
	QHBoxLayout *lout_btns = new QHBoxLayout();

	lout_btns->addWidget(btn_add);
	lout_btns->addWidget(btn_edit);
	lout_btns->addWidget(btn_delete);

	lout_main->addWidget(graph);
	lout_main->addLayout(lout_btns);

	QWidget *qwL = new QWidget();
	qwL->setLayout(lout_main);

	QSplitter *splt_main = new QSplitter(Qt::Horizontal);

	splt_main->addWidget(qwL);

	this->setCentralWidget(splt_main);
}

QtView::~QtView() {

}
