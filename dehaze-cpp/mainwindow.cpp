#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    test();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::test()
{
    QString load_image_file_name("/home/nvidia/work/python/dehaze/image/channel_01.jpg");

    cv::Mat load=cv::imread( load_image_file_name.toStdString() );
    cv::Mat result;

    for( int i = 0; i < 1000; ++i)
    {
        int64 start_t = cv::getTickCount();
        haze.dehaze( load, result );
        int64 end_t = cv::getTickCount();

        float run_t = ( end_t - start_t ) * 1000.0 / cv::getTickFrequency();
        std::cout << " dez:" << run_t << " ms" << std::endl;
    }

    cv::imshow( "src", load );
    cv::imshow( "result", result );
    cv::waitKey(0);

}
