#ifndef UPDATELOGWINDOW_H
#define UPDATELOGWINDOW_H

#include <QDialog>

namespace Ui {
class UpDateLogWindow;
}

class UpDateLogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UpDateLogWindow(QWidget *parent = nullptr);
    ~UpDateLogWindow();

private:
    Ui::UpDateLogWindow *ui;
};

#endif // UPDATELOGWINDOW_H
