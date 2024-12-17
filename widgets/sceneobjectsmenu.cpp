#include "sceneobjectsmenu.h"
#include "ui_sceneobjectsmenu.h"

SceneObjectsMenu::SceneObjectsMenu(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::SceneObjectsMenu)
{
    ui->setupUi(this);
    setFrameShape(QFrame::Box);
    setLineWidth(10);

    ui->comboBox->addItem("Kitchen");
    ui->comboBox->addItem("Bedroom");
    ui->comboBox->addItem("Bathroom");

    ui->lineEdit->setPlaceholderText("Search...");
}

SceneObjectsMenu::~SceneObjectsMenu()
{
    delete ui;
}
