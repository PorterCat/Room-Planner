#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "room-editor/roomeditor.h"

#include <QActionGroup>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->centralwidget->setLayout(ui->gridLayout);

	QActionGroup *actionGroup = new QActionGroup(this);
	actionGroup->setExclusive(true);
	// add there brush and other things
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
	ui->tabWidget->removeTab(index);
}

void MainWindow::on_actionNew_Project_triggered()
{
	RoomEditor* tab = new RoomEditor(32, 32, ui->tabWidget);
	QSizePolicy p(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
	tab->setSizePolicy(p);
	tab->setFixedSize(20, 20);
	ui->tabWidget->setCurrentIndex(ui->tabWidget->addTab(tab, "Untitled"));
}
