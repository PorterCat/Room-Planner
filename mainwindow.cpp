#include "mainwindow.h"
#include "tools/cursortool.h"
#include "tools/doortool.h"
#include "tools/dragtool.h"
#include "tools/walltool.h"
#include "tools/removeTool.h"
#include "ui_mainwindow.h"
#include "room-editor/roomeditor.h"

#include <QActionGroup>
#include <QMessageBox>
#include <QFileDialog>

#include "widgets/newproject_inputdialog.h"

#include <room-editor/sceneserializer.h>

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
    actionGroup->addAction(ui->actionDeleteTool);
    actionGroup->addAction(ui->actionDoorTool);

    sceneObjectsMenu_ = new SceneObjectsMenu(this);
    sceneObjectsMenu_->setGeometry(50, 50, 300, 400);
    sceneObjectsMenu_->hide();

    ui->actionDragTool->setChecked(true);
    setCurrentTool(new DragTool());


    // Changing cursor Update: left it for good days
    // connect(ui->actionCursorTool, &QAction::triggered, this, &MainWindow::setCursorForAction);
    // connect(ui->actionDeleteTool, &QAction::triggered, this, &MainWindow::setCursorForAction);


    // Just for highlight the selected option in toolBoxes
    ui->generalTools->setStyleSheet(
        "QToolButton:checked { background-color: lightgray; border: 1px solid gray; }");
    ui->buildTools->setStyleSheet(
        "QToolButton:checked { background-color: lightgray; border: 1px solid gray; }");
}

MainWindow::~MainWindow() { delete ui; }

bool MainWindow::isTabSelected()
{
    int currentIndex = ui->tabWidget->currentIndex();
    if (currentIndex == -1)
    {
        QMessageBox::information(this, tr("No Tab Selected"), tr("No tab is selected."));
        return false;
    }
    return true;
}

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
        RoomEditor* tab = new RoomEditor(dialog.getWidthValue(), dialog.getLengthValue(), dialog.getFileNameValue(), ui->tabWidget, this);
        tab->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding));
        ui->tabWidget->setCurrentIndex(ui->tabWidget->addTab(tab, dialog.getFileNameValue()));
    }
}

void MainWindow::setCurrentTool(ITool* tool)
{
    currentTool_ = tool;
    emit currentToolChanged(currentTool_);
}

void MainWindow::setCursorForAction() //works good but pictures are awful))
{
    QAction* action = qobject_cast<QAction*>(sender());
    if (action)
    {
        QPixmap pixmap = action->icon().pixmap(QSize(32, 32));
        QCursor cursor(pixmap);
        setCursor(cursor);
    }
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

void MainWindow::on_actionUndo_triggered()
{
    if (auto roomEditor = dynamic_cast<RoomEditor*>(ui->tabWidget->currentWidget()))
    {
        QUndoStack* undoStack = roomEditor->getScene()->undoStack();
        if (undoStack->canUndo())
            undoStack->undo();
    }
}

void MainWindow::on_actionRedo_triggered()
{
    if (auto roomEditor = dynamic_cast<RoomEditor*>(ui->tabWidget->currentWidget()))
    {
        QUndoStack* undoStack = roomEditor->getScene()->undoStack();
        if (undoStack->canRedo())
            undoStack->redo();
    }
}

#pragma region Tools

void MainWindow::on_actionDragTool_toggled(bool arg1)
{
    if (arg1) // What happens when you click on new tool
    {
        this->setCurrentTool(new DragTool());
        QList<RoomEditor*> roomEditors = ui->tabWidget->findChildren<RoomEditor*>();
        for (RoomEditor* editor : roomEditors)
            editor->setDragMode(true);
        return;
    }
    //What happens when you select another tool
    QList<RoomEditor*> roomEditors = ui->tabWidget->findChildren<RoomEditor*>();
    for (RoomEditor* editor : roomEditors)
        editor->setDragMode(false);
}

void MainWindow::on_actionWallTool_toggled(bool arg1)
{
    if (arg1)
    {
        this->setCurrentTool(new WallTool());
        QList<RoomEditor*> roomEditors = ui->tabWidget->findChildren<RoomEditor*>();
        for (RoomEditor* editor : roomEditors)
        {
            editor->setSelectPointsMode(true);
            editor->setPointsHidden(false);
        }
        return;
    }
    QList<RoomEditor*> roomEditors = ui->tabWidget->findChildren<RoomEditor*>();
    for (RoomEditor* editor : roomEditors)
    {
        editor->setSelectPointsMode(false);
        editor->setPointsHidden(true);
    }
}

void MainWindow::on_actionDeleteTool_toggled(bool arg1)
{
    if (arg1)
    {
        this->setCurrentTool(new RemoveTool());
        return;
    }
}

void MainWindow::on_actionCursorTool_toggled(bool arg1)
{
    if (arg1)
    {
        this->setCurrentTool(new CursorTool());
        return;
    }
}

void MainWindow::on_actionDoorTool_toggled(bool arg1)
{
    if (arg1)
    {
        this->setCurrentTool(new DoorTool());
        return;
    }
}

#pragma endregion



bool MainWindow::on_actionSave_As_triggered()
{
    if (!isTabSelected()) return false;

    QString filePath;
    RoomEditor* roomEditor = dynamic_cast<RoomEditor*>(ui->tabWidget->currentWidget());

    if (roomEditor)
    {
        filePath = QFileDialog::getSaveFileName(this, tr("Save File"), roomEditor->getFileName(), tr("Files (*.json)"));

        if (!filePath.isEmpty())
        {
            if (roomEditor->saveScene(filePath))
            {
                ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), QFileInfo(filePath).fileName());
                return true;
            }
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Unsupported Widget"), tr("The current widget does not support saving."));
    }

    return false;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("All (*json)"));
    if (filePath.isEmpty())
    {
        QMessageBox::information(this, tr("No File Selected"), tr("No file was selected."));
        return;
    }

    RoomEditor* roomEditor = SceneSerializer::loadScene(filePath, ui->tabWidget, this);

    if(roomEditor)
    {
        roomEditor->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding));
        ui->tabWidget->setCurrentIndex(ui->tabWidget->addTab(roomEditor, roomEditor->getFileName()));
    }
}

