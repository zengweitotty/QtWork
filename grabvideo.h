#ifndef GRABVIDEO_H
#define GRABVIDEO_H

#include <QThread>
#include <QDebug>
#include <QImage>
#include "cv.h"
#include "highgui.h"

class GrabVideo : public QThread
{
    Q_OBJECT
private:
    CvCapture* capture; //初始化从摄像头获取视频
    IplImage *pImg; //OpenCV读取图像数据
    QImage *tempImg;    //转换后QImage类型的数据
public:
    explicit GrabVideo(QObject *parent = 0);
    ~GrabVideo();
signals:
    void sendQImage(QImage *img);
protected:
    void run();
};

#endif // GRABVIDEO_H
