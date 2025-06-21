
#include "qtview.h"

using namespace std;


QtView::QtView(SolarSystem *solarSystem): QMainWindow() {
	setWindowTitle("Solar System Simulator");

	model = solarSystem;

	// graphics
	scene = new QGraphicsScene(-100, -100, 1000, 800);
	scene->setBackgroundBrush(Qt::black);


	graphicsView = new QGraphicsView(scene);
	graphicsView->setRenderHints(QPainter::Antialiasing);
	graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
	graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);


	// control buttons
	qBtnAdd = new QPushButton("Add");
	qBtnEdit = new QPushButton("Edit");
	qBtnDelete = new QPushButton("Delete");
	qBtnRun = new QPushButton("Run");
	qBtnReset = new QPushButton("Reset");
	qBtnSetG = new QPushButton("Set G");


	// input fields
	qTxtName = new QLineEdit();
	qTxtName->setPlaceholderText("Name");
	qTxtName->setAlignment(Qt::AlignJustify);

	qTxtPosX = new QLineEdit();
	qTxtPosX->setPlaceholderText("Position X");

	qTxtPosY = new QLineEdit();
	qTxtPosY->setPlaceholderText("Position Y");

	qTxtDofX = new QLineEdit();
	qTxtDofX->setPlaceholderText("Dof X");

	qTxtDofY = new QLineEdit();
	qTxtDofY->setPlaceholderText("Dof Y");

	qTxtMass = new QLineEdit();
	qTxtMass->setPlaceholderText("Mass");

	qTxtSize = new QLineEdit();
	qTxtSize->setPlaceholderText("Size");

	progBar = new QProgressBar(this);
	progBar->setMinimum(0);
	progBar->setMaximum(100);
	progBar->setValue(0);


	qCBoxColor = new QComboBox(this);
	qCBoxColor->setInsertPolicy(QComboBox::NoInsert);
	QStringList colors;
	colors << "White" << "Red" << "Dark Red" << "Green" << "Dark Green" << "Blue" << "Dark Blue"
			<< "Cyan" << "Dark Cyan" << "Magenta" << "Dark Magenta" << "Yellow" << "Dark Yellow";
	qCBoxColor->addItems(colors);


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
	loutCtrl->addWidget(qCBoxColor, 11, 0, 1, 2, Qt::AlignJustify);

	loutCtrl->addWidget(progBar, 12, 0, 1, 2, Qt::AlignJustify);


	// Misc
	QDockWidget *dock = new QDockWidget("Controlls", this);
	dock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	dock->setWidget(new QWidget());
	dock->widget()->setLayout(loutCtrl);

	addDockWidget(Qt::RightDockWidgetArea, dock);
	setCentralWidget(graphicsView);


	// setup ellipse and animations
	timer = new QTimeLine();

	for (int i = 0; i < MAX_PLANETS; i++) {
		ellipse[i] = NULL;
		anims[i] = NULL;
	}

	QGraphicsEllipseItem *test = scene->addEllipse(
			QRectF(0, 0, 3, 3),
			QPen(Qt::SolidLine), QBrush(Qt::white));

	updateView();
}

QtView::~QtView() {

}

void QtView::addEllipse(int id) {
	Planet *planet = model->getPlanet(id);
	double size = planet->size.get_d();
	double posx = planet->pos.x.get_d() - (planet->size.get_d() / 2);
	double posy = planet->pos.y.get_d() - (planet->size.get_d() / 2);

	ellipse[id] = scene->addEllipse(QRectF(posx, posy, size, size),
			QPen(Qt::SolidLine), QBrush(Qt::white));
	ellipse[id]->setFlag(QGraphicsItem::ItemIsSelectable, true);
	ellipse[id]->setBrush(translateColor(planet->color));

	anims[id] = new QGraphicsItemAnimation();
	anims[id]->setItem(ellipse[id]);
	anims[id]->setTimeLine(timer);
}

void QtView::delEllipse(int id) {
	delete ellipse[id];
	ellipse[id] = NULL;

	delete anims[id];
	ellipse[id] = NULL;
}

void QtView::animate(int count) {
	model->setCtrlState(false);

	int duration = 1000;
	if (count *10 > 1000)
		duration = count *10;

	timer->setDuration(duration);
	timer->setFrameRange(0, duration);

	model->resetProgBar(duration);

	for (int i = 0; i < count; i++) {
		model->tick();
		model->setProgBarValue(i);
		for (int j = 0; j < MAX_PLANETS; j++) {
			Planet *planet = model->getPlanet(j);
			if (planet != NULL) {
				double posx = planet->pos.x.get_d();
				double posy = planet->pos.y.get_d();

				double step = (double) i / count;
				anims[j]->setPosAt(step, QPointF(posx, posy));
			}
		}
	}
	timer->start();
}

void QtView::updateView() {
	for (int i = 0; i < MAX_PLANETS; i++) {
		Planet *planet = model->getPlanet(i);
		QGraphicsEllipseItem *graph = ellipse[i];

		if (planet != NULL && graph != NULL) {
			ellipse[i]->setPos(QPointF(planet->pos.x.get_d(), planet->pos.y.get_d()));
			ellipse[i]->setBrush(translateColor(planet->color));
		} else if (planet != NULL && graph == NULL) {
			addEllipse(i);
		} else if (planet == NULL && graph != NULL) {
			delEllipse(i);
		}
	}
}

void QtView::clearAnimations() {
	for (int i = 0; i < MAX_PLANETS; i++) {
		if (ellipse[i] != NULL)
			anims[i]->clear();
	}
}

void QtView::updatePlanetInfo() {
	int frameCount = model->getFrameCount();

	if (progBar->maximum() != frameCount)
		progBar->setMaximum(frameCount);

	if (model->getProgBarValue() >= 0)
		progBar->setValue(model->getProgBarValue());

	int id = model->getSelectedPlanetID();
	if (id >= 0) {
		Planet *planet = model->getPlanet(id);

		qTxtName->setText(QString::fromStdString(planet->name));
		qTxtPosX->setText(QString::number(planet->pos.x.get_d(), 'f', 3));
		qTxtPosY->setText(QString::number(planet->pos.y.get_d(), 'f', 3));
		qTxtDofX->setText(QString::number(planet->dof.x.get_d(), 'f', 3));
		qTxtDofY->setText(QString::number(planet->dof.y.get_d(), 'f', 3));
		qTxtMass->setText(QString::number(planet->mass.get_d(), 'f', 3));
		qTxtSize->setText(QString::number(planet->size.get_d(), 'f', 3));
		int i = qCBoxColor->findText(QString::fromStdString(planet->color));
		if (i >= 0)
			qCBoxColor->setCurrentIndex(i);
	} else {
		qTxtName->setText("");
		qTxtPosX->setText("");
		qTxtPosY->setText("");
		qTxtDofX->setText("");
		qTxtDofY->setText("");
		qTxtMass->setText("");
		qTxtSize->setText("");
		qCBoxColor->setCurrentIndex(0);
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
	qCBoxColor->setEnabled(state);
}

void QtView::updateSelection() {
	if (!scene->selectedItems().isEmpty()) {
		QGraphicsItem *focused = scene->selectedItems().first();

		for (int i = 0; i < MAX_PLANETS; i++) {
			if (model->getPlanet(i) != NULL) {
				if (focused == ellipse[i]) {
					model->setSelectedPlanetID(i);
					i = MAX_PLANETS;
				}
			}
		}

	} else {
		model->setSelectedPlanetID(-1);
	}
}

QColor QtView::translateColor(string color) {
	if (!color.compare("White"))
		return Qt::white;
	else if (!color.compare("Red"))
		return Qt::red;
	else if (!color.compare("Dark Red"))
		return Qt::darkRed;
	else if (!color.compare("Green"))
		return Qt::green;
	else if (!color.compare("Dark Green"))
		return Qt::darkGreen;
	else if (!color.compare("Blue"))
		return Qt::blue;
	else if (!color.compare("Dark Blue"))
		return Qt::darkBlue;
	else if (!color.compare("Cyan"))
		return Qt::cyan;
	else if (!color.compare("Dark Cyan"))
		return Qt::darkCyan;
	else if (!color.compare("Magenta"))
		return Qt::magenta;
	else if (!color.compare("Dark Magenta"))
		return Qt::darkMagenta;
	else if (!color.compare("Yellow"))
		return Qt::yellow;
	else if (!color.compare("Dark Yellow"))
		return Qt::darkYellow;

	return Qt::white;
}
