#ifndef FURNITUREEDITOR_H
#define FURNITUREEDITOR_H

#include "room-editor/scene-objects/refurniture.h"
#include <QScrollBar>
#include <QVBoxLayout>
#include <QWidget>
#include <qlabel.h>

class FurnitureEditor : public QWidget
{
    Q_OBJECT

public:
    FurnitureEditor(QWidget* parent = nullptr) : QWidget(parent)
    {
        // Создаем скроллбары
        m_sizeSlider = new QScrollBar(Qt::Horizontal, this);
        m_sizeSlider->setRange(50, 200); // Диапазон размеров (50% - 200%)
        m_sizeSlider->setValue(100);     // По умолчанию 100%

        m_rotationSlider = new QScrollBar(Qt::Horizontal, this);
        m_rotationSlider->setRange(0, 360); // Диапазон поворота (0° - 360°)
        m_rotationSlider->setValue(0);      // По умолчанию 0°

        // Создаем лейаут и добавляем скроллбары
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(new QLabel("Size"));
        layout->addWidget(m_sizeSlider);
        layout->addWidget(new QLabel("Rotation"));
        layout->addWidget(m_rotationSlider);

        // Подключаем сигналы скроллбаров к слотам
        connect(m_sizeSlider, &QScrollBar::valueChanged, this, &FurnitureEditor::onSizeChanged);
        connect(m_rotationSlider, &QScrollBar::valueChanged, this, &FurnitureEditor::onRotationChanged);
    }

    void setSelectedFurniture(REFurniture* furniture)
    {
        m_selectedFurniture = furniture; // Сохраняем указатель на выделенный объект

        if (furniture) // Если объект выделен
        {
            // Синхронизируем скроллбары с параметрами объекта
            m_sizeSlider->setValue(furniture->getScale() * 100); // Масштаб в процентах
            m_rotationSlider->setValue(furniture->getRotation()); // Угол поворота
        }
        else // Если объект не выделен
        {
            // Сбрасываем скроллбары в начальные значения
            m_sizeSlider->setValue(100); // 100% (исходный размер)
            m_rotationSlider->setValue(0); // 0° (исходный поворот)
        }
    }

private slots:
    void onSizeChanged(int value)
    {
        if (m_selectedFurniture)
        {
            qreal scale = value / 100.0; // Преобразуем значение в масштаб
            m_selectedFurniture->setScale(scale);
        }
    }

    void onRotationChanged(int value)
    {
        if (m_selectedFurniture)
        {
            m_selectedFurniture->setRotation(value);
        }
    }

private:
    QScrollBar* m_sizeSlider;
    QScrollBar* m_rotationSlider;
    REFurniture* m_selectedFurniture = nullptr;
};

#endif // FURNITUREEDITOR_H
