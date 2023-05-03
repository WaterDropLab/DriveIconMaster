#include "aboutwindow.h"
#include "ui_aboutwindow.h"
#include <updatelogwindow.h>
AboutWindow::AboutWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    setAttribute(Qt::WA_DeleteOnClose);
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::on_btnabtus_3_clicked()
{
    UpDateLogWindow *wn=new UpDateLogWindow;
    wn->exec();

}
