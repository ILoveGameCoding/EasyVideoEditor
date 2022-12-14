#pragma once

#include <QWidget>
#include <QString>
#include <QLabel>
#include <opencv2/opencv.hpp>
#include <QFile>
#include <QDateTime>

class UsefulFunction
{
public:
    static int getMillisecondsFromString(QString timeString);
    static QString getStringFromMilliseconds(int milliseconds);
    static QString getDetailStringFromSeconds(int seconds);
    static QString kor(std::string korString);
    static void showMatToLabel(QLabel* qlabel, cv::Mat* mat, cv::Size resizeData, int top, int down, int left, int right);
    static void writeLog(QString filePath, QString tag, QString message);
    static QImage matToQImage(cv::Mat* mat);
    static cv::Mat QImageToMat(QImage* qimage);
};

