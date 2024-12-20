#include "sceneobjectsmenu.h"
#include "room-editor/roomeditor.h"
#include "ui_sceneobjectsmenu.h"
#include <QGraphicsProxyWidget>
#include <room-editor/scene-objects/refurniture.h>
#include <mainwindow.h>
#include "room-editor/actiongraphicsscene.h"


SceneObjectsMenu::SceneObjectsMenu(QSharedPointer<FurnitureDatabase> db, QWidget* parent)
    : QFrame(parent)
    , ui(new Ui::SceneObjectsMenu)
    , m_db(db)
{
    ui->setupUi(this);
    setFrameShape(QFrame::Box);
    setLineWidth(10);

    QList<QString> categories = m_db->getCategories();
    for (const QString& category : categories)
    {
        ui->comboBox->addItem(category);
    }

    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &SceneObjectsMenu::onCategoryChanged);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &SceneObjectsMenu::onItemClicked);
    ui->lineEdit->setPlaceholderText("Search...");

}

void SceneObjectsMenu::onCategoryChanged(const QString& category)
{
    // Очищаем QListWidget
    ui->listWidget->clear();

    // Загружаем мебель по категории
    loadFurnitureByCategory(category);
}

void SceneObjectsMenu::onItemClicked(QListWidgetItem* item)
{
    QString imagePath = item->data(Qt::UserRole).toString();

    MainWindow* mainWindow = qobject_cast<MainWindow*>(parent());
    if (!mainWindow)
    {
        qWarning() << "Parent is not MainWindow!";
        return;
    }

    QWidget* currentWidget = mainWindow->getCurrentWidget();
    if (!currentWidget)
    {
        qWarning() << "No current widget in tabWidget!";
        return;
    }

    RoomEditor* roomEditor = qobject_cast<RoomEditor*>(currentWidget);
    if (!roomEditor)
    {
        qWarning() << "Current widget is not RoomEditor!";
        return;
    }

    ActionGraphicsScene* scene = roomEditor->getScene();
    if (!scene)
    {
        qWarning() << "Scene is not available!";
        return;
    }

    REFurniture* furniture = new REFurniture(imagePath, 0, 0);
    scene->addItemWithUndo(furniture);
}

void SceneObjectsMenu::loadFurnitureByCategory(const QString& category)
{
    int id = m_db->getCategoryIdByName(category);

    if (id != -1)
    {
        QList<QPair<QString, QString>> furnitureList = m_db->getFurnitureByCategory(id);

        for (const auto& item : furnitureList)
        {
            QString name = item.first;
            QString imagePath = item.second;

            QListWidgetItem* listItem = new QListWidgetItem(name, ui->listWidget);
            listItem->setData(Qt::UserRole, imagePath);
        }
    }
}

SceneObjectsMenu::~SceneObjectsMenu()
{
    delete ui;
}
