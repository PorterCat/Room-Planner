#include "popuplabel.h"

PopupLabel::PopupLabel(QWidget *parent)
	: QLabel(parent)
{
	timer = new QTimer(this);
	timer->setSingleShot(true);
	timer->setInterval(2000);
	connect(timer, &QTimer::timeout, this, &QLabel::hide);
}
