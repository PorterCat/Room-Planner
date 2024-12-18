#pragma once

#include <QKeyEvent>
#include <QWidget>

class IKeyTool 
{
public:
    virtual ~IKeyTool() = default;
    virtual void keyPressEvent(QKeyEvent* event, QWidget* sender) = 0;
    virtual void keyReleaseEvent(QKeyEvent* event, QWidget* sender) = 0;
};
