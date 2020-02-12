#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

class DisplayerWidget;
class ScaleWindow;
class QMenu;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    DisplayerWidget *m_displayerWidget;
    ScaleWindow *m_scaleWindow;
    void initMenus();
    void initWidgets();

    QMenu *m_fileMenu;
        QAction *m_openImageAction;
        QAction *m_saveImageAction;
        QAction *m_closeImageAction;
        QAction *m_quitAction;

    QMenu *m_editMenu;
        QAction *m_scaleAction;

private slots:
        void openImageAction();
        void saveImageAction();
        void closeImageAction();
        void scaleImageAction();
};

#endif // MAINWINDOW_H
