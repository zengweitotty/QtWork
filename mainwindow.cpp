#include "mainwindow.h"
/*显示线程*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /*界面编程*/
    stop = 0;
    ok = new QPushButton("Start");  //初始化按键的初值
    label = new QLabel();

    connect(ok,SIGNAL(clicked()),this,SLOT(getFrame()));
    grabThread = new GrabVideo;
    connect(grabThread,SIGNAL(sendQImage(QImage*)),this,SLOT(getQImage(QImage*)));

    /*布局*/
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(label);
    mainLayout->addWidget(ok);
    main = new QWidget;
    main->setLayout(mainLayout);
    setCentralWidget(main);

}
void MainWindow::getFrame(){
    if(stop == 1){  //之前是Stop状态
        stop = 0;
        ok->setText("Start");
        grabThread->terminate();
        grabThread->wait();
    }else{//之前是Start状态
        stop = 1;
        ok->setText("Stop");
        grabThread->start();
    }
}
void MainWindow::getQImage(QImage *img){
    qDebug() << "Get video from Cam";
    label->setPixmap(QPixmap::fromImage(*img));
}

MainWindow::~MainWindow()
{

    delete ok;
    delete label;
    delete mainLayout;
    delete main;
}
