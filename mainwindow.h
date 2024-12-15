#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tools/itool.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

  public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

  private slots:
	void on_tabWidget_tabCloseRequested(int index);

	void on_actionNew_Project_triggered();

	void on_actionWallTool_triggered();

  private:
	Ui::MainWindow *ui;
	ITool* _currentTool;
};
#endif // MAINWINDOW_H
