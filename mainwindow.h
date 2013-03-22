#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QPixmap>
#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include "grabvideo.h"
#include "cv.h"
#include "highgui.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *main;  //�����ڵ�Widget
    QVBoxLayout *mainLayout;    //�����ڵĲ���
    QPushButton *ok;    //�����ڵİ���
    QPixmap *imagePixmap;   //�����ڵ���ʾ�豸
    QLabel *label;  //�����ڵ���ʾLabel
    GrabVideo *grabThread;
    bool stop;  //��Ƶͼ��Ķ�ȡ����ͣ
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void getFrame();
    void getQImage(QImage *img);
};

#endif // MAINWINDOW_H
