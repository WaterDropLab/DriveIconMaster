
#ifndef ABOUTUSWINDOW_H
#define ABOUTUSWINDOW_H

#include <QMainWindow>

namespace Ui {
class AboutUsWindow;
}

class AboutUsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AboutUsWindow(QWidget *parent = nullptr);
    ~AboutUsWindow();

private:
    Ui::AboutUsWindow *ui;
};

#endif // ABOUTUSWINDOW_H
