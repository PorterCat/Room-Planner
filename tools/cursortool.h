#ifndef CURSORTOOL_H
#define CURSORTOOL_H

#include "itool.h"

class CursorTool : public ITool
{
public:
    CursorTool();
    ~CursorTool();
    void mousePressEvent(QMouseEvent* event, QWidget* sender) override;
    void mouseMoveEvent(QMouseEvent* event, QWidget* sender) override;
    void mouseReleaseEvent(QMouseEvent* event, QWidget* sender) override;
};

#endif // CURSORTOOL_H
