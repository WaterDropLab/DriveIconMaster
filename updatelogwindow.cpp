#include "updatelogwindow.h"
#include "ui_updatelogwindow.h"

UpDateLogWindow::UpDateLogWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpDateLogWindow)
{
    ui->setupUi(this);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    setAttribute(Qt::WA_DeleteOnClose);
}

UpDateLogWindow::~UpDateLogWindow()
{
    delete ui;
}
