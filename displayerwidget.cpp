#include "displayerwidget.h"
#include "mainwindow.h"
#include "scaler.h"
#include <iostream>
#include <QVBoxLayout>
#include <cmath>
using namespace std;

DisplayerWidget::DisplayerWidget(MainWindow *parent)
    : QWidget(parent), m_mainWindow(parent) {

    m_scaler = new Scaler();
    imageContainer = new QLabel();
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(imageContainer);
    m_layout->setAlignment(Qt::AlignJustify);
}

DisplayerWidget::~DisplayerWidget() {
    delete imageContainer;
    delete m_scaler;
    delete m_layout;
}

void DisplayerWidget::open(QString path) {
    imageObject = QImage(path);
    m_scaler->setImage(imageObject);
    m_mainWindow->resize(imageObject.width(), imageObject.height());

    imageContainer->setPixmap(QPixmap::fromImage(imageObject));
    imageContainer->adjustSize();
    imageContainer->show();
    update();
}

void DisplayerWidget::save(QString path) {
    imageObject.save(path, 0, 100);
}

void DisplayerWidget::close() {
    imageObject = QImage();
    imageContainer->clear();
    update();
}

void DisplayerWidget::doScale(int width, int height) {
    bool wReduce = imageObject.width() > width;
    bool hReduce = imageObject.height() > height;
    int deltaWidth = abs(width - imageObject.width());
    int deltaHeight = abs(height - imageObject.height());
    m_mainWindow->setDisabled(true);
    while (deltaWidth > 0 || deltaHeight > 0) {
        if (deltaWidth > 0) {
            if (wReduce) m_scaler->scale(-1, false);
            else m_scaler->scale(1, false);
            deltaWidth--;
        }
        if (deltaHeight > 0) {
            if (hReduce) m_scaler->scale(-1, true);
            else m_scaler->scale(1, true);
            deltaHeight--;
        }
        imageObject = m_scaler->getImage();
        imageContainer->setPixmap(QPixmap::fromImage(imageObject));
        imageContainer->adjustSize();
        imageContainer->repaint();
    }
    m_mainWindow->setDisabled(false);
    update();
}

int DisplayerWidget::getImageWidth() {
    return imageObject.width();
}

int DisplayerWidget::getImageHeight() {
    return imageObject.height();
}
