#ifndef SCENEOBJECTSMENU_H
#define SCENEOBJECTSMENU_H

#include <QFrame>
#include <QMouseEvent>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QListWidgetItem>
#include <room-editor/furniture-db/furnituredatabase.h>

namespace Ui {
class SceneObjectsMenu;
}

class SceneObjectsMenu : public QFrame
{
    Q_OBJECT

public:
    explicit SceneObjectsMenu(QSharedPointer<FurnitureDatabase> db, QWidget* parent = nullptr);
    ~SceneObjectsMenu();

    void loadFurnitureByCategory(const QString& category);

protected:
    void mousePressEvent(QMouseEvent *event) override {
        QWidget *child = childAt(event->pos());
        if (!child || child == this) {
            if (event->button() == Qt::LeftButton) {
                dragPosition = event->globalPos() - frameGeometry().topLeft();
                event->accept();
            }
        } else {
            event->ignore();
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - dragPosition);
            event->accept();
        }
    }

private slots:
    void onCategoryChanged(const QString& category);
    void onItemClicked(QListWidgetItem* item);

private:
    Ui::SceneObjectsMenu *ui;
    QPoint dragPosition;
    QSharedPointer<FurnitureDatabase> m_db;
};

#endif // SCENEOBJECTSMENU_H
