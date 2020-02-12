#ifndef SCALEWINDOW_H
#define SCALEWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QMainWindow>

class DisplayerWidget;

class ScaleWindow : public QWidget {
    Q_OBJECT
public:
    ScaleWindow(QWidget *parent = 0);
    ~ScaleWindow();
    void setTargetDisplayer(DisplayerWidget* target);
    void initializeFields();
private:
    QMainWindow* m_mainWindow;
    DisplayerWidget* m_targetDisplayer;

    QGridLayout* layout;
    QLabel* heightLabel;
    QLabel* widthLabel;
    QSpinBox* heightInput;
    QSpinBox* widthInput;
    QPushButton* scaleButton;
public slots:
    void scaleImage();
};

#endif // SCALEWINDOW_H
