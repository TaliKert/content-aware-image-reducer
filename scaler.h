#ifndef SCALER_H
#define SCALER_H

#include <QImage>
#include <map>
#include <tuple>
#include <vector>
#include <QTransform>

using namespace std;

class Scaler {
public:
    Scaler();
    ~Scaler();
    void scaleWidth(int n);
    void scaleHeight(int n);
    void setImage(QImage image);
    QImage getImage();
    void scale(int n, bool isVertical);
    double pixelWeight(int x, int y);
//private:
    QImage subject;
    QTransform* rotatorL;
    QTransform* rotatorR;
    map<int, int> findSlice();
    void removeSlice(map<int, int> slice);
    void addSlice(map<int, int> slice);
};

#endif // SCALER_H
