#ifndef POPUPLABEL_H
#define POPUPLABEL_H

#include <QLabel>
#include <QTimer>

class PopupLabel : public QLabel
{
	Q_OBJECT

  public:
	explicit PopupLabel(QWidget *parent = nullptr);

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
		timer->start(2000);
	}

  private:
	QTimer *timer;
};

#endif // POPUPLABEL_H
