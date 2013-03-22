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
    CvCapture* capture; //��ʼ��������ͷ��ȡ��Ƶ
    IplImage *pImg; //OpenCV��ȡͼ������
    QImage *tempImg;    //ת����QImage���͵�����
public:
    explicit GrabVideo(QObject *parent = 0);
    ~GrabVideo();
signals:
    void sendQImage(QImage *img);
protected:
    void run();
};

#endif // GRABVIDEO_H
