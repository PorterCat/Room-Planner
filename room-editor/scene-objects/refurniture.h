#ifndef REFURNITURE_H
#define REFURNITURE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsProxyWidget>
#include <QObject>
#include "iroomeditorobject.h"
#include <QGraphicsView>

class REFurniture : public QGraphicsPixmapItem, public virtual IRoomEditorObject
{
public:
    REFurniture(const QString& imagePath, qreal x, qreal y, QGraphicsItem* parent = nullptr);
    ~REFurniture();

    qreal getScale() const { return scale(); }
    qreal getRotation() const { return rotation(); }

    int type() const override { return ObjectType::REFurnitureType; }
    QString typeName() const override { return "REFurniture"; }

    QJsonObject toJson() const override;

    static REFurniture* fromJson(const QJsonObject& json);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

private:
    QString imagePath_;

    QGraphicsProxyWidget* m_sizeSliderProxy = nullptr;
    QGraphicsProxyWidget* m_rotationSliderProxy = nullptr;
    QGraphicsProxyWidget* m_sizeLabelProxy = nullptr;
    QGraphicsProxyWidget* m_rotationLabelProxy = nullptr;

    QObject* m_signalHandler = nullptr;

    void createSliders();
    void removeSliders();
    void updateSlidersPosition();
    void onSizeChanged(int value);
    void onRotationChanged(int value);
};

#endif // REFURNITURE_H
