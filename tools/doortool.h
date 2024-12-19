#ifndef DOORTOOL_H
#define DOORTOOL_H

#include "itool.h"
#include "ikeytool.h"
#include "room-editor/scene-objects/redoor.h"

class DoorTool : public ITool, public IKeyTool
{
public:
    DoorTool();
    ~DoorTool();
    void mousePressEvent(QMouseEvent* event, QWidget* sender) override;
    void mouseMoveEvent(QMouseEvent* event, QWidget* sender) override;
    void mouseReleaseEvent(QMouseEvent* event, QWidget* sender) override;
    
    void keyPressEvent(QKeyEvent* event, QWidget* sender) override;
    void keyReleaseEvent(QKeyEvent* event, QWidget* sender) override;

private:
    QGraphicsRectItem* previewDoor_;
    QGraphicsLineItem* previewLine_;
    bool perpendicularDirectionRight_;
    bool doorDirectionRight_;
};

#endif // DOORTOOL_H
