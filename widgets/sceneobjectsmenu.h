#ifndef SCENEOBJECTSMENU_H
#define SCENEOBJECTSMENU_H

#include <QFrame>
#include <QMouseEvent>

namespace Ui {
class SceneObjectsMenu;
}

class SceneObjectsMenu : public QFrame
{
    Q_OBJECT

public:
    explicit SceneObjectsMenu(QWidget *parent = nullptr);
    ~SceneObjectsMenu();

protected:
    void mousePressEvent(QMouseEvent *event) override {
        QWidget *child = childAt(event->pos());
        if (!child || child == this) {
            // Если нажатие произошло на пустое место или на рамку, начинаем перетаскивание
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

private:
    Ui::SceneObjectsMenu *ui;
    QPoint dragPosition;
};

#endif // SCENEOBJECTSMENU_H
