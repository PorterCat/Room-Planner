#ifndef ITOOL_H
#define ITOOL_H

#include <QMouseEvent>

class ITool
{
  public:
	virtual ~ITool() {}
	virtual void mousePressEvent(QMouseEvent *event) = 0;
	virtual void mouseMoveEvent(QMouseEvent *event) = 0;
	virtual void mouseReleaseEvent(QMouseEvent *event) = 0;
};

#endif // ITOOL_H
