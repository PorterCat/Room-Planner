#include "mainwindow.h"
#include "tools/dragtool.h"
#include "tools/walltool.h"
#include "ui_mainwindow.h"
#include "room-editor/roomeditor.h"

#include <QActionGroup>
#include <QMessageBox>

#include "widgets/newproject_inputdialog.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->centralwidget->setLayout(ui->gridLayout);

	QActionGroup *actionGroup = new QActionGroup(this);
	actionGroup->setExclusive(true);
	actionGroup->addAction(ui->actionWallTool);
	actionGroup->addAction(ui->actionDragTool);
    actionGroup->addAction(ui->actionCursorTool);

	ui->actionDragTool->setChecked(true);
	setCurrentTool(new DragTool());

    // add there brush and other things

    ui->generalTools->setStyleSheet(
        "QToolButton:checked { background-color: lightgray; border: 1px solid gray; }"
    );
    ui->buildTools->setStyleSheet(
        "QToolButton:checked { background-color: lightgray; border: 1px solid gray; }"
    );
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
	ui->tabWidget->removeTab(index);
}

void MainWindow::on_actionNew_Project_triggered()
{
	NewProjectInputDialog dialog(this);
	if (dialog.exec() == QDialog::Accepted) 
	{
		RoomEditor* tab = new RoomEditor(dialog.getWidthValue(), dialog.getLengthValue(), ui->tabWidget, this);
		tab->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding));
		ui->tabWidget->setCurrentIndex(ui->tabWidget->addTab(tab, dialog.getFileNameValue()));
	}
}

void MainWindow::setCurrentTool(ITool* tool)
{
	currentTool_ = tool;
	emit currentToolChanged(currentTool_);
}

// Turn tools into list

void MainWindow::on_actionDragTool_toggled(bool arg1)
{
	if(arg1)
	{
		setCurrentTool(new DragTool());
		return;
	}
	QList<RoomEditor*> roomEditors = ui->tabWidget->findChildren<RoomEditor*>();
	for (RoomEditor* editor : roomEditors)
		editor->setDragMode(false);
}

void MainWindow::on_actionWallTool_toggled(bool arg1)
{
	if(arg1)
	{
		setCurrentTool(new WallTool());
		return;
	}
}


void MainWindow::on_actionClose_Tab_triggered()
{
    //TO DO: add there maybesave? options
    ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tabWidget->currentWidget()));
}


void MainWindow::on_actionClose_All_triggered()
{
    for (int i = 0; i < ui->tabWidget->count(); ++i)
    {
        QWidget* currentWidget = ui->tabWidget->widget(i);

        if (currentWidget)
        {
            QMessageBox::StandardButton reply = QMessageBox::warning(this, tr("Unsaved Changes"),
                                            tr("You have unsaved changes. Do you want to save them?"),
                                            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            if (reply == QMessageBox::Save) {
                //saveAsTriggered;
            }
            else if (reply == QMessageBox::Cancel)
                return;
        }
    }
}

