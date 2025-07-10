#include "calculateTransformedImage.h"
#include <opencv2/opencv.hpp>
#include <QJSValue>
#include <QImage>
#include <QBuffer>
#include <QDebug>


void CalculateTransformedImage::rotateImage(const QImage &input, qreal angle, QJSValue callback) {
    // Convert QImage to OpenCV Mat
    QImage formatted = input.convertToFormat(QImage::Format_ARGB32);
    cv::Mat mat(formatted.height(), formatted.width(), CV_8UC4,
                const_cast<uchar*>(formatted.bits()), formatted.bytesPerLine());

    // Rotate image
    cv::Point2f center(mat.cols / 2.0F, mat.rows / 2.0F);
    cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
    cv::Mat rotated;
    cv::warpAffine(mat, rotated, rot, mat.size());

    // Convert back to QImage
    QImage output(rotated.data, rotated.cols, rotated.rows, rotated.step, QImage::Format_ARGB32);
    QImage copy = output.copy();  // Deep copy to avoid referencing released memory

    // Convert to base64 URI
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    copy.save(&buffer, "PNG");

    QString uri = "data:image/png;base64," + ba.toBase64();

    // Call back into QML
    if (callback.isCallable()) {
        QJSValueList args;
        args << QJSValue(uri);
        callback.call(args);
    }
}

