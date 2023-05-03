#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>

namespace Ui {
class StartWindow;
}

class StartWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();
     QTimer * tm;

private:
    Ui::StartWindow *ui;
private slots:
    void slot_tm_timout();


};

#endif // STARTWINDOW_H
