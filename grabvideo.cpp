#include "grabvideo.h"
/*���������߳�*/
GrabVideo::GrabVideo(QObject *parent) :
    QThread(parent)
{
    /*���ܱ��*/
    capture = cvCreateCameraCapture(0);    //��ʼ������ͷ��ȡ��Ƶ
    cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH,320);
    cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT,240);
    cvSetCaptureProperty(capture,CV_CAP_PROP_FPS,20);
}
void GrabVideo::run(){
    while(true){
        pImg = cvQueryFrame(capture);
        uchar *qImageBuffer = NULL;
        int x ,y = 0;
        int width = pImg->width;
        int height = pImg->height;
        int widthStep = pImg->widthStep;
        /*struct IplImage to QImage*/
        switch(pImg->depth){
        case IPL_DEPTH_8U:  //OpenCV ͼ�����8U
            qDebug("IplImage Depth is IPL_DEPTH_8U");
            if(pImg->nChannels == 1){
                qDebug("IplImage nChannel is 1");
                qImageBuffer = (uchar*)malloc(width * height * sizeof(uchar));
                uchar *QImagePtr = qImageBuffer;
                const uchar *IplImagePtr = (const uchar*)pImg->imageData;
                for(y = 0;y < height;y++){
                    memcpy(QImagePtr,IplImagePtr,width);
                    QImagePtr += width;
                    IplImagePtr += widthStep;
                }
                tempImg = new QImage(qImageBuffer,width,height,QImage::Format_Indexed8);
            }else if(pImg->nChannels == 3){
                qDebug("IplImage nChannel is 3");
                qImageBuffer = (uchar*)malloc(4 * width * height * sizeof(uchar));
                uchar *QImagePtr = qImageBuffer;
                const uchar *IplImagePtr = (const uchar*)pImg->imageData;
                for(y = 0;y < height;y++){
                    for(x = 0;x < width;x++){
                        QImagePtr[0] = IplImagePtr[0];
                        QImagePtr[1] = IplImagePtr[1];
                        QImagePtr[2] = IplImagePtr[2];
                        QImagePtr[3] = 0;
                        QImagePtr += 4;
                        IplImagePtr += 3;
                    }
                    IplImagePtr += widthStep-3*width;
                }
                tempImg = new QImage(qImageBuffer,width,height,QImage::Format_RGB32);
            }else{
                qDebug("Camera IplImage channels can not support");
            }
            break;
        case IPL_DEPTH_16U: //OpenCV ͼ�����16U
            qDebug("IplImage Depth is IPL_DEPTH_16U");
            break;
        case IPL_DEPTH_32F://OpenCV ͼ�����32U
            qDebug("IplImage Depth is IPL_DEPTH_16U");
            break;
        case IPL_DEPTH_64F://OpenCV ͼ�����64U
            qDebug("IplImage Depth is IPL_DEPTH_16U");
            break;
        }
        emit sendQImage(tempImg);
    }
}
GrabVideo::~GrabVideo(){
    delete pImg;
    cvReleaseCapture(&capture);
    delete tempImg;
}

