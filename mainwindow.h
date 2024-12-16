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

	void setCurrentTool(ITool* tool);
	ITool* currentTool() const { return currentTool_; }

  signals:
	void currentToolChanged(ITool* newTool);

  private slots:
	void on_tabWidget_tabCloseRequested(int index);

	void on_actionNew_Project_triggered();

	void on_actionDragTool_toggled(bool arg1);

	void on_actionWallTool_toggled(bool arg1);

    void on_actionClose_Tab_triggered();

    void on_actionClose_All_triggered();

private:
	Ui::MainWindow *ui;
	ITool* currentTool_;
};
#endif // MAINWINDOW_H
