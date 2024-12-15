#include "mainwindow.h"
#include "tools/dragtool.h"
#include "tools/walltool.h"
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
	actionGroup->addAction(ui->actionWallTool);
	actionGroup->addAction(ui->actionDragTool);

	ui->actionDragTool->setChecked(true);
	setCurrentTool(new DragTool());
	// add there brush and other things
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
	ui->tabWidget->removeTab(index);
}

void MainWindow::on_actionNew_Project_triggered()
{
	RoomEditor* tab = new RoomEditor(32, 32, ui->tabWidget, this);
	tab->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding));
	ui->tabWidget->setCurrentIndex(ui->tabWidget->addTab(tab, "Untitled"));
}

void MainWindow::setCurrentTool(ITool* tool)
{
	currentTool_ = tool;
	emit currentToolChanged(currentTool_);
}

// Turn them into list

void MainWindow::on_actionWallTool_triggered()
{
	setCurrentTool(new WallTool());
}

void MainWindow::on_actionDragTool_triggered()
{
	setCurrentTool(new DragTool());
}

