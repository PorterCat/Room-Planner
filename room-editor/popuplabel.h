#ifndef POPUPLABEL_H
#define POPUPLABEL_H

#include <QLabel>
#include <QTimer>

class PopupLabel : public QLabel
{
	Q_OBJECT

  public:
	explicit PopupLabel(QWidget *parent = nullptr, int interval = 2000);

  signals:
	void doubleClicked();
	void clicked();

  protected:
	void mouseDoubleClickEvent(QMouseEvent *event) override
	{
		QLabel::mouseDoubleClickEvent(event);
		emit doubleClicked();
	}

	void mousePressEvent(QMouseEvent *event) override
	{
		QLabel::mousePressEvent(event);
		emit clicked();
	}

  public slots:
	void showWithTimer()
	{
		this->show();
		timer->start();
	}

	void showWithTimer(int interval)
	{
		timer->setInterval(interval);
		this->show();
		timer->start();
	}

  private:
	QTimer *timer;
};

#endif // POPUPLABEL_H
