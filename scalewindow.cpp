#include "scalewindow.h"
#include "displayerwidget.h"
#include <iostream>

ScaleWindow::ScaleWindow(QWidget *parent) : QWidget(parent) {
    this->setFixedSize(200, 100);
    this->setWindowTitle(QString("Select dimensions"));
    layout = new QGridLayout(this);

    heightLabel = new QLabel;
    heightLabel->setText(QString("Height:"));
    layout->addWidget(heightLabel, 0, 0, 1, 1, Qt::AlignRight);

    widthLabel = new QLabel;
    widthLabel->setText(QString("Width:"));
    layout->addWidget(widthLabel, 1, 0, 1, 1, Qt::AlignRight);

    heightInput = new QSpinBox;
    heightInput->setMinimum(1);
    heightInput->setMaximum(9999);
    heightInput->setMinimumWidth(100);
    heightInput->setSingleStep(1);
    layout->addWidget(heightInput, 0, 1, 1, 1, Qt::AlignLeft);

    widthInput = new QSpinBox;
    widthInput->setMinimum(1);
    widthInput->setMaximum(9999);
    widthInput->setMinimumWidth(100);
    widthInput->setSingleStep(1);
    layout->addWidget(widthInput, 1, 1, 1, 1, Qt::AlignLeft);

    scaleButton = new QPushButton;
    scaleButton->setText("Scale");
    scaleButton->setMinimumWidth(100);
    layout->addWidget(scaleButton, 2, 0, 1, 2, Qt::AlignCenter);
    connect(scaleButton, SIGNAL(pressed()), this, SLOT(scaleImage()));
}

ScaleWindow::~ScaleWindow() {
    delete scaleButton;
    delete widthInput;
    delete heightInput;
    delete widthLabel;
    delete heightLabel;
    delete layout;
}

void ScaleWindow::setTargetDisplayer(DisplayerWidget* target) {
    m_targetDisplayer = target;
}

void ScaleWindow::initializeFields() {
    heightInput->setValue(m_targetDisplayer->getImageHeight());
    widthInput->setValue(m_targetDisplayer->getImageWidth());
}

void ScaleWindow::scaleImage() {
    this->close();
    m_targetDisplayer->doScale(widthInput->value(), heightInput->value());
}
