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
    QWidget *main;  //主窗口的Widget
    QVBoxLayout *mainLayout;    //主窗口的布局
    QPushButton *ok;    //主窗口的按键
    QPixmap *imagePixmap;   //主窗口的显示设备
    QLabel *label;  //主窗口的显示Label
    GrabVideo *grabThread;
    bool stop;  //视频图像的读取或暂停
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void getFrame();
    void getQImage(QImage *img);
};

#endif // MAINWINDOW_H
