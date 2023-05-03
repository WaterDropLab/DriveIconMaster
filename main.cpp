#include "mainwindow.h"
#include <QApplication>
#include <startwindow.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    StartWindow *start=new StartWindow;
    start->show();

    return a.exec();
}
