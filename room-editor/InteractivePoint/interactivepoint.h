#ifndef INTERACTIVEPOINT_H
#define INTERACTIVEPOINT_H

#include <QWidget>

class InteractivePoint : public QWidget
{
	Q_OBJECT
  public:
	explicit InteractivePoint(QWidget *parent = nullptr);

  protected:
	// void mouseMoveEvent(QMouseEvent* e) override;

  private:
	QPoint position_;

  signals:
};

#endif // INTERACTIVEPOINT_H
