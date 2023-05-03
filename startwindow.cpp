#include "startwindow.h"
#include "ui_startwindow.h"
#include <QTimer>
#include <mainwindow.h>
StartWindow::StartWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setWindowOpacity(0.8);
   tm=new QTimer();
    tm->setInterval(3000);
    tm->start();
    connect(tm,SIGNAL(timeout()),this,SLOT(slot_tm_timout()));
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::slot_tm_timout()
{

    MainWindow *w=new MainWindow;
    w->show();
    this->close();

}
