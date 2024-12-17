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
    ui->centralwidget->setLayout(ui->centralLayout);

    ui->buttonLayout->addStretch();
    ui->buttonLayout->addWidget(ui->pushButton);


    //Remember: every action there should switch currentTool_ !!!
    QActionGroup *actionGroup = new QActionGroup(this);
    actionGroup->setExclusive(true);
    actionGroup->addAction(ui->actionWallTool);
    actionGroup->addAction(ui->actionDragTool);
    actionGroup->addAction(ui->actionCursorTool);

    sceneObjectsMenu_ = new SceneObjectsMenu(this);
    sceneObjectsMenu_->setGeometry(50, 50, 300, 400);
    sceneObjectsMenu_->hide();

    ui->actionDragTool->setChecked(true);
    setCurrentTool(new DragTool());


    // Just for highlight the selected option in toolBoxes
    ui->generalTools->setStyleSheet(
        "QToolButton:checked { background-color: lightgray; border: 1px solid gray; }");
    ui->buildTools->setStyleSheet(
        "QToolButton:checked { background-color: lightgray; border: 1px solid gray; }");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    //TO DO: add there maybesave? option
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
        this->setCurrentTool(new DragTool());
        QList<RoomEditor*> roomEditors = ui->tabWidget->findChildren<RoomEditor*>();
        for (RoomEditor* editor : roomEditors)
            editor->setDragMode(true);
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
        this->setCurrentTool(new WallTool());
        QList<RoomEditor*> roomEditors = ui->tabWidget->findChildren<RoomEditor*>();
        for (RoomEditor* editor : roomEditors)
            editor->setSelectPointsMode(true);
        return;
    }
    QList<RoomEditor*> roomEditors = ui->tabWidget->findChildren<RoomEditor*>();
    for (RoomEditor* editor : roomEditors)
        editor->setSelectPointsMode(false);
}


void MainWindow::on_actionClose_Tab_triggered()
{
    //TO DO: add there maybesave? option
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

void MainWindow::on_pushButton_clicked()
{
    if(sceneObjectsMenu_->isVisible())
        sceneObjectsMenu_->hide();
    else
        sceneObjectsMenu_->show();
}


void MainWindow::on_actionOpen_triggered()
{

}


void MainWindow::on_actionUndo_triggered()
{
    if (auto roomEditor = dynamic_cast<RoomEditor*>(ui->tabWidget->currentWidget()))
    {
        QUndoStack* undoStack = roomEditor->getScene()->undoStack();
        if (undoStack->canUndo())
        {
            undoStack->undo();
        }
    }
}

void MainWindow::on_actionRedo_triggered()
{
    if (auto roomEditor = dynamic_cast<RoomEditor*>(ui->tabWidget->currentWidget()))
    {
        QUndoStack* undoStack = roomEditor->getScene()->undoStack();
        if (undoStack->canRedo())
        {
            undoStack->redo();
        }
    }
}

