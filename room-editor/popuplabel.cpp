#include "popuplabel.h"

PopupLabel::PopupLabel(QWidget *parent, int interval)
	: QLabel(parent)
{
	timer = new QTimer(this);
	timer->setSingleShot(true);
	timer->setInterval(interval);
	connect(timer, &QTimer::timeout, this, &QLabel::hide);
}
