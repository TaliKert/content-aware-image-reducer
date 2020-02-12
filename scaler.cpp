#include "scaler.h"
#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

Scaler::Scaler(){
    rotatorL = new QTransform();
    rotatorR = new QTransform();
    rotatorL->rotate(90);
    rotatorR->rotate(270);
}

Scaler::~Scaler(){
    delete rotatorL;
    delete rotatorR;
}

void Scaler::setImage(QImage source) {
    subject = source;
}

QImage Scaler::getImage() {
    return subject;
}

void Scaler::scaleHeight(int n) {
    scale(n, false);
}

void Scaler::scaleWidth(int n) {
    scale(n, true);
}

void Scaler::scale(int n, bool isVertical) {
    bool isreduce = false;
    if (n < 0) {
        isreduce = true;
        n = -n;
    }
    if (isVertical) {
        subject = subject.transformed(*rotatorL);
    }
    for (int i = 0; i < n; i++) {
        map<int, int> slice = findSlice();
        if (isreduce) removeSlice(slice);
        else addSlice(slice);
    }
    if (isVertical) {
        subject = subject.transformed(*rotatorR);
    }
}

void Scaler::removeSlice(map<int, int> slice) {
    for (int y = 0; y < subject.height(); y++) {
        QRgb* line = (QRgb*) subject.scanLine(y);
        for (int x = slice[y]; x < subject.width() - 1; x++) {
            line[x] = line[x+1];
        }
    }
    subject = subject.copy(0, 0, subject.width() - 1, subject.height());
}

void Scaler::addSlice(map<int, int > slice) {
    subject = subject.copy(0, 0, subject.width() + 1, subject.height());
    for (int y = 0; y < subject.height(); y++) {
        QRgb* line = (QRgb*) subject.scanLine(y);
        for (int x = subject.width() - 1; x > slice[y]; x--) {
            line[x] = line[x - 1];
        }
    }
}

// this is where the fun begins...
map<int, int> Scaler::findSlice() {
    double* weights = new double[subject.height() * subject.width()];
    int* markers = new int[subject.height() * subject.width()];
    map<int, int> result;

    for (int x = 0; x < subject.width(); x++ ) {
        weights[x] = pixelWeight(x, 0);
    }

    for (int y = 1; y < subject.height(); y++) {
        for (int x = 0; x < subject.width(); x++) {
            int marker = -1;
            double least = numeric_limits<double>::max();
            for (int side = -1; side < 2; side++) {
                if (x + side < subject.width() && x + side >= 0 && least > weights[(y-1)*subject.width() + x + side]) {
                    least = weights[(y-1)*subject.width() + x + side];
                    marker = side;
                }
            }
            weights[y*subject.width() + x] = pixelWeight(x, y) + least;
            markers[y*subject.width() + x] = x + marker;
        }
    }

    double least = numeric_limits<double>::max();
    int nextNode = -1;

    for (int x = 0; x < subject.width(); x++) {
        if (weights[(subject.height() - 1)*subject.width() + x] < least) {
            least = weights[(subject.height() - 1)*subject.width() + x];
            nextNode = x;
        }
    }

    for (int y = subject.height() - 1; y >= 0; y--) {
        for (int x = 0; x < subject.width(); x++) {
            if (x == nextNode) {
                result[y] = x;
            }
        }
        nextNode = markers[y*subject.width() + nextNode];
    }

    delete[] weights;
    delete[] markers;
    return result;
}

double Scaler::pixelWeight(int x, int y) {
    if (x == 0 || y == 0 || subject.width() - 1 == x || subject.height() - 1 == y)
        return 1000;
    double dX = 0;
    double dY = 0;
    for (int i = 0; i < 3; i++) {
        dX += pow((int)(subject.pixel(x + 1, y) >> (8 * i) & 0xFF) - (int)(subject.pixel(x - 1, y) >> (8 * i) & 0xFF), 2);
        dY += pow((int)(subject.pixel(x, y + 1) >> (8 * i) & 0xFF) - (int)(subject.pixel(x, y - 1) >> (8 * i) & 0xFF), 2);
    }
    return sqrt(dX + dY);
}
