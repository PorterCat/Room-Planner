#ifndef REMOVETOOL_H
#define REMOVETOOL_H

#include "itool.h"

class RemoveTool : public ITool
{
public:
    RemoveTool();
    ~RemoveTool();
    void mousePressEvent(QMouseEvent* event, QWidget* sender) override;
    void mouseMoveEvent(QMouseEvent* event, QWidget* sender) override;
    void mouseReleaseEvent(QMouseEvent* event, QWidget* sender) override;
};

#endif // REMOVETOOL_H
