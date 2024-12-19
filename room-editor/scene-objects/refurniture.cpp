#include "refurniture.h"
#include <QGraphicsSceneMouseEvent>
#include <QJsonObject>

#include "widgets/furnitureeditor.h"

REFurniture::REFurniture(const QString& imagePath, qreal x, qreal y, QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent), imagePath_(imagePath)
{
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull())
    {
        setPixmap(pixmap);
    }
    else
    {
        //qWarning() << "Failed to load image:" << imagePath;
    }

    setPos(x, y);
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}

QJsonObject REFurniture::toJson() const
{
    QJsonObject json;
    json["type"] = typeName();
    json["x"] = pos().x();
    json["y"] = pos().y();
    json["width"] = pixmap().width();
    json["height"] = pixmap().height();
    json["imagePath"] = imagePath_;
    return json;
}

REFurniture* REFurniture::fromJson(const QJsonObject& json)
{
    qreal x = json["x"].toDouble();
    qreal y = json["y"].toDouble();
    QString imagePath = json["imagePath"].toString();

    REFurniture* furniture = new REFurniture(imagePath, x, y);
    furniture->setPos(x, y);
    return furniture;
}

FurnitureEditor* findEditor(QGraphicsScene* scene)
{
    if (scene)
    {
        QList<QGraphicsView*> views = scene->views();
        for (QGraphicsView* view : views)
        {
            if (FurnitureEditor* editor = view->findChild<FurnitureEditor*>())
            {
                return editor;
            }
        }
    }
    return nullptr;
}

QVariant REFurniture::itemChange(GraphicsItemChange change, const QVariant& value)
{
    if (change == QGraphicsItem::ItemSelectedChange)
    {
        if (value.toBool()) // Если объект выделен
        {
            createSliders(); // Создаем скроллбары
        }
        else // Если объект сняли с выделения
        {
            removeSliders(); // Удаляем скроллбары
        }
    }
    return QGraphicsPixmapItem::itemChange(change, value);
}

void REFurniture::createSliders()
{
    if (!scene())
        return;

    // Создаем скроллбар для изменения размера
    QScrollBar* sizeSlider = new QScrollBar(Qt::Horizontal);
    sizeSlider->setRange(50, 200); // Диапазон размеров (50% - 200%)
    sizeSlider->setValue(100);     // По умолчанию 100%

    // Создаем скроллбар для поворота
    QScrollBar* rotationSlider = new QScrollBar(Qt::Horizontal);
    rotationSlider->setRange(0, 360); // Диапазон поворота (0° - 360°)
    rotationSlider->setValue(0);      // По умолчанию 0°

    // Добавляем скроллбары на сцену через QGraphicsProxyWidget
    m_sizeSliderProxy = scene()->addWidget(sizeSlider);
    m_rotationSliderProxy = scene()->addWidget(rotationSlider);

    // Размещаем скроллбары рядом с объектом
    QPointF pos = this->scenePos();
    m_sizeSliderProxy->setPos(pos.x(), pos.y() - 30); // Под объектом
    m_rotationSliderProxy->setPos(pos.x(), pos.y() - 60); // Под размером

    // Подключаем сигналы скроллбаров к слотам с использованием лямбда-функций
    // QObject::connect(sizeSlider, &QScrollBar::valueChanged, this, [this](int value) {
    //     qreal scale = value / 100.0;
    //     this->setScale(scale);
    // });

    // QObject::connect(rotationSlider, &QScrollBar::valueChanged, this, [this](int value) {
    //     this->setRotation(value);
    // });
}
void REFurniture::removeSliders()
{
    if (m_sizeSliderProxy)
    {
        scene()->removeItem(m_sizeSliderProxy);
        delete m_sizeSliderProxy;
        m_sizeSliderProxy = nullptr;
    }

    if (m_rotationSliderProxy)
    {
        scene()->removeItem(m_rotationSliderProxy);
        delete m_rotationSliderProxy;
        m_rotationSliderProxy = nullptr;
    }
}

void REFurniture::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    setSelected(true);
    QGraphicsPixmapItem::mousePressEvent(event);
}

void REFurniture::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsPixmapItem::mouseMoveEvent(event);
}

void REFurniture::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}
