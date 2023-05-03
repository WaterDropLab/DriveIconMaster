#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QString>
#include <QFileInfo>
#include <QImage>
extern QString icopth;
namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addcmbdrv();
    void inicmbdrv();
    void setdrvico();

private slots:
    void slot_cmbdrv_currentTextChanged();
    void slot_btnapp_clicked();
    void slot_btnref_clicked();
    void slot_btndef_clicked();
    void slot_btnopn_clicked();
    void slot_btnabt_clicked();
    void slot_btnabtus_clicked();
    void on_cmbdrv_currentTextChanged(const QString &arg1);



    void on_btnfeedback_clicked();

    void on_btnabtus_3_clicked();

    void on_commandLinkButton_clicked();

    void on_btnapp_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
