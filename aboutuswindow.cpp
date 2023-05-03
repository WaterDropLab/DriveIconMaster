#include "aboutuswindow.h"
#include "ui_aboutuswindow.h"

AboutUsWindow::AboutUsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AboutUsWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->textEdit);
    setAttribute(Qt::WA_DeleteOnClose);
}

AboutUsWindow::~AboutUsWindow()
{
    delete ui;
}
