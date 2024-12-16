#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QFormLayout>

class NewProjectInputDialog : public QDialog
{
	Q_OBJECT

public:
    explicit NewProjectInputDialog(QWidget* parent = nullptr);

    QString getFileNameValue() const;
    int getWidthValue() const;
    int getLengthValue() const;

private:
    QLineEdit* fileNameLineEdit_;
    QSpinBox* widthSpinBox_;  
    QSpinBox* lengthSpinBox_;  
};
