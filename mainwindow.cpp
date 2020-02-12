#include "mainwindow.h"
#include "displayerwidget.h"
#include "scalewindow.h"

#include <QAction>
#include <QApplication>
#include <QEvent>
#include <QMenu>
#include <QLabel>
#include <QMenuBar>
#include <QFileDialog>
#include <QGridLayout>
#include <QSpinBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setMinimumSize(800, 600);
    initMenus();
    initWidgets();
}

MainWindow::~MainWindow() {
}

void MainWindow::initMenus() {
    // FILE
    m_fileMenu = new QMenu(this);
    m_fileMenu->setTitle(QString("&File"));
    menuBar()->addMenu(m_fileMenu);
    // FILE > _OPEN
    m_openImageAction = new QAction(this);
    m_openImageAction->setText(QString("&Open"));
    m_fileMenu->addAction(m_openImageAction);
    connect(m_openImageAction, SIGNAL(triggered()), this, SLOT(openImageAction()));
    // FILE > _SAVE
    m_saveImageAction = new QAction(this);
    m_saveImageAction->setText(QString("&Save"));
    m_fileMenu->addAction(m_saveImageAction);
    connect(m_saveImageAction, SIGNAL(triggered()), this, SLOT(saveImageAction()));
    // FILE > _CLOSE
    m_closeImageAction = new QAction(this);
    m_closeImageAction->setText(QString("&Close"));
    m_fileMenu->addAction(m_closeImageAction);
    connect(m_closeImageAction, SIGNAL(triggered()), this, SLOT(closeImageAction()));
    // FILE > _QUIT
    m_quitAction = new QAction(this);
    m_quitAction->setText(QString("&Quit"));
    m_fileMenu->addAction(m_quitAction);
    connect(m_quitAction, SIGNAL(triggered()), this, SLOT(close()));

    // EDIT
    m_editMenu = new QMenu(this);
    m_editMenu->setTitle(QString("&Edit"));
    menuBar()->addMenu(m_editMenu);
    // EDIT > _SCALE
    m_scaleAction = new QAction(this);
    m_scaleAction->setText(QString("&Scale"));
    m_editMenu->addAction(m_scaleAction);
    connect(m_scaleAction, SIGNAL(triggered()), this, SLOT(scaleImageAction()));
}

void MainWindow::initWidgets() {
    m_displayerWidget = new DisplayerWidget(this);
    setCentralWidget(m_displayerWidget);
    m_scaleWindow = new ScaleWindow();
    m_scaleWindow->setTargetDisplayer(m_displayerWidget);
    m_scaleAction->setDisabled(true);
    m_saveImageAction->setDisabled(true);
    m_closeImageAction->setDisabled(true);
}

void MainWindow::openImageAction() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "./", tr("Images (*.png *.jpg *.bmp *.gif *.ppm)"));
    if (fileName.isEmpty()) return;
    m_displayerWidget->open(fileName);
    m_scaleAction->setDisabled(false);
    m_saveImageAction->setDisabled(false);
    m_closeImageAction->setDisabled(false);
}

void MainWindow::saveImageAction() {
    QString path = QFileDialog::getSaveFileName(this, tr("Save As"), "./", tr("Images (*.png *.jpg *.bmp *.gif *.ppm)"));
    m_displayerWidget->save(path);
}

void MainWindow::closeImageAction() {
    m_displayerWidget->close();
    m_scaleAction->setDisabled(true);
    m_saveImageAction->setDisabled(true);
    m_closeImageAction->setDisabled(true);
}

void MainWindow::scaleImageAction() {
    m_scaleWindow->initializeFields();
    m_scaleWindow->show();
}
