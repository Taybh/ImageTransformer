#ifndef CALCULATETRANSFORMEDIMAGE_H
#define CALCULATETRANSFORMEDIMAGE_H

#include <QObject>
#include <QImage>
#include <QJSValue>

class CalculateTransformedImage : public QObject {
    Q_OBJECT
public:
    Q_INVOKABLE void rotateImage(const QImage &input, qreal angle, QJSValue callback);
};

#endif
