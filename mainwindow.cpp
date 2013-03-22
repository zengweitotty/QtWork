#include "mainwindow.h"
/*��ʾ�߳�*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /*������*/
    stop = 0;
    ok = new QPushButton("Start");  //��ʼ�������ĳ�ֵ
    label = new QLabel();

    connect(ok,SIGNAL(clicked()),this,SLOT(getFrame()));
    grabThread = new GrabVideo;
    connect(grabThread,SIGNAL(sendQImage(QImage*)),this,SLOT(getQImage(QImage*)));

    /*����*/
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(label);
    mainLayout->addWidget(ok);
    main = new QWidget;
    main->setLayout(mainLayout);
    setCentralWidget(main);

}
void MainWindow::getFrame(){
    if(stop == 1){  //֮ǰ��Stop״̬
        stop = 0;
        ok->setText("Start");
        grabThread->terminate();
        grabThread->wait();
    }else{//֮ǰ��Start״̬
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
