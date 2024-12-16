#include "newproject_inputdialog.h"

NewProjectInputDialog::NewProjectInputDialog(QWidget* parent)
    : QDialog(parent) 
{
    QFormLayout* formLayout = new QFormLayout(this);

    fileNameLineEdit_ = new QLineEdit(this);
    formLayout->addRow("File Name:", fileNameLineEdit_);

    widthSpinBox_ = new QSpinBox(this);
    widthSpinBox_->setRange(1, 128);
    widthSpinBox_->setValue(24);
    formLayout->addRow("Width:", widthSpinBox_);

    lengthSpinBox_ = new QSpinBox(this);
    lengthSpinBox_->setRange(1, 128); 
    lengthSpinBox_->setValue(24);
    formLayout->addRow("Height:", lengthSpinBox_);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, this);
    formLayout->addRow(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

QString NewProjectInputDialog::getFileNameValue() const {
    return fileNameLineEdit_->text().isEmpty() ? "untitled" : fileNameLineEdit_->text();
}

int NewProjectInputDialog::getWidthValue() const {
    return widthSpinBox_->value();
}

int NewProjectInputDialog::getLengthValue() const {
    return lengthSpinBox_->value();
}