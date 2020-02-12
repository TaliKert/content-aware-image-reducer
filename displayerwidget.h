#ifndef DISPLAYERWIDGET_H
#define DISPLAYERWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QImage>
#include <QLabel>
#include <QPixmap>

class MainWindow;
class Scaler;

class DisplayerWidget: public QWidget {
    Q_OBJECT
public:
    DisplayerWidget(MainWindow *parent = 0);
    ~DisplayerWidget();

    void open(QString path);
    void save(QString path);
    void close();
    void doScale(int width, int height);

    int getImageWidth();
    int getImageHeight();
protected:
    MainWindow *m_mainWindow;
    Scaler *m_scaler;
private:
    QImage imageObject;
    QLabel *imageContainer;
    QLayout *m_layout;

};

#endif // DISPLAYERWIDGET_H
