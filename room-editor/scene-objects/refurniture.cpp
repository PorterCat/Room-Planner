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
    setScale(0.1);
    setPos(x, y);
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    setTransformOriginPoint(boundingRect().center());
}

REFurniture::~REFurniture()
{
    removeSliders();
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
    json["rotation"] = rotation();
    json["scale"] = scale();
    return json;
}

REFurniture* REFurniture::fromJson(const QJsonObject& json)
{
    qreal x = json["x"].toDouble();
    qreal y = json["y"].toDouble();
    QString imagePath = json["imagePath"].toString();

    REFurniture* furniture = new REFurniture(imagePath, x, y);
    furniture->setPos(x, y);

    if (json.contains("rotation") && json["rotation"].isDouble())
    {
        furniture->setRotation(json["rotation"].toDouble());
    }

    if (json.contains("scale") && json["scale"].isDouble())
    {
        furniture->setScale(json["scale"].toDouble());
    }

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
    else if (change == QGraphicsItem::ItemPositionChange) // При перемещении объекта
    {
        updateSlidersPosition(); // Обновляем позицию скроллбаров
    }
    return QGraphicsPixmapItem::itemChange(change, value);
}


void REFurniture::createSliders()
{
    if (!scene())
        return;

    QScrollBar* sizeSlider = new QScrollBar(Qt::Vertical);
    sizeSlider->setRange(10, 200); 
    sizeSlider->setValue(this->scale() * 100);
    sizeSlider->setFixedHeight(100); 
    sizeSlider->setStyleSheet("QScrollBar { background: #e0e0e0; }");

    QScrollBar* rotationSlider = new QScrollBar(Qt::Vertical);
    rotationSlider->setRange(0, 360);
    rotationSlider->setValue(this->rotation());
    rotationSlider->setFixedHeight(100); 
    rotationSlider->setStyleSheet("QScrollBar { background: #e0e0e0; }");

    QLabel* sizeLabel = new QLabel("Size");
    QLabel* rotationLabel = new QLabel("Rotation");

    sizeLabel->setStyleSheet("QLabel { background: transparent; color: black; }");
    rotationLabel->setStyleSheet("QLabel { background: transparent; color: black; }");

    m_sizeSliderProxy = scene()->addWidget(sizeSlider);
    m_rotationSliderProxy = scene()->addWidget(rotationSlider);
    m_sizeLabelProxy = scene()->addWidget(sizeLabel);
    m_rotationLabelProxy = scene()->addWidget(rotationLabel);

    updateSlidersPosition();

    QObject::connect(sizeSlider, &QScrollBar::valueChanged, [this](int value) {
        this->onSizeChanged(value);
        });

    QObject::connect(rotationSlider, &QScrollBar::valueChanged, [this](int value) {
        this->onRotationChanged(value);
        });
}

void REFurniture::updateSlidersPosition()
{
    if (!m_sizeSliderProxy || !m_rotationSliderProxy || !m_sizeLabelProxy || !m_rotationLabelProxy)
        return;

    // Получаем текущую позицию объекта
    QPointF pos = this->scenePos();

    // Фиксированное смещение слева
    qreal sliderOffset = -30; // Смещение слева
    qreal labelOffset = 30; // Смещение для надписей

    // Размещаем скроллбары слева от объекта
    m_sizeSliderProxy->setPos(pos.x() + sliderOffset, pos.y());
    m_rotationSliderProxy->setPos(pos.x() + sliderOffset, pos.y() + m_sizeSliderProxy->boundingRect().height() + 10);

    // Размещаем надписи
    m_sizeLabelProxy->setPos(pos.x() + sliderOffset, pos.y() - labelOffset);
    m_rotationLabelProxy->setPos(pos.x() + sliderOffset, pos.y() + m_sizeSliderProxy->boundingRect().height() + 10 - labelOffset);
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

    if (m_sizeLabelProxy)
    {
        scene()->removeItem(m_sizeLabelProxy);
        delete m_sizeLabelProxy;
        m_sizeLabelProxy = nullptr;
    }

    if (m_rotationLabelProxy)
    {
        scene()->removeItem(m_rotationLabelProxy);
        delete m_rotationLabelProxy;
        m_rotationLabelProxy = nullptr;
    }
}

void REFurniture::onRotationChanged(int value)
{
    this->setRotation(value); // Устанавливаем угол поворота объекта
}

void REFurniture::onSizeChanged(int value)
{
    qreal scale = value / 100.0;
    this->setScale(scale);
}

void REFurniture::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    setSelected(true);
    QGraphicsPixmapItem::mousePressEvent(event);
}

void REFurniture::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    updateSlidersPosition();
    QGraphicsPixmapItem::mouseMoveEvent(event);
}

void REFurniture::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    updateSlidersPosition();
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}
