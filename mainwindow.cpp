#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDialog>
#include <QDir>
#include <QFile>
#include <QIcon>
#include <QStorageInfo>
#include <QSettings>
#include <QWidget>
#include <QFileDialog>
#include <stdlib.h>
#include <aboutuswindow.h>
#include <aboutwindow.h>
#include <qt_windows.h>
#include <windows.h>
#include <qdebug.h>
#include <QProcess>
#include <QDesktopServices>
#include <QUrl>

QString icopth;

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnref,SIGNAL(clicked()),this,SLOT(slot_btnref_clicked()));
    connect(ui->btnapp,SIGNAL(clicked()),this,SLOT(slot_btnapp_clicked()));
    connect(ui->cmbdrv,SIGNAL(currentTextChanged()),this,SLOT(slot_cmbdrv_currentTextChanged()));
    connect(ui->btnopn,SIGNAL(clicked()),this,SLOT(slot_btnopn_clicked()));
    connect(ui->btndef,SIGNAL(clicked()),this,SLOT(slot_btndef_clicked()));
    connect(ui->btnabt,SIGNAL(clicked()),this,SLOT(slot_btnabt_clicked()));
    connect(ui->btnabtus,SIGNAL(clicked()),this,SLOT(slot_btnabtus_clicked()));
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);


//    setWindowOpacity(0.1);
    ui->lblico->setScaledContents(1);
    ui->txtpath->clear();
    inicmbdrv();

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::addcmbdrv()

{
    QList<QStorageInfo> drvinfolist=QStorageInfo::mountedVolumes();

    QIcon ico;

    foreach (QStorageInfo storage,drvinfolist)
    {
      if(storage.isReady())
      {

          if (QFile::exists(storage.rootPath().mid(0,3)+"autorun.inf"))
          {
              QSettings ini(storage.rootPath().mid(0,3)+"autorun.inf",QSettings::IniFormat);
              ini.beginGroup("Autorun");
              if(QFile::exists(storage.rootPath().mid(0,3)+ini.value("ICON").toString()))
              {
                  QIcon ico(storage.rootPath().mid(0,3)+ini.value("ICON").toString());
                  ui->cmbdrv->addItem(ico,storage.rootPath().mid(0,2)+"    名称："+storage.name()+"   文件系统类型："+storage.fileSystemType());
              }
              else{
                  if (storage.rootPath().mid(0,1)=="C"){
                  QIcon ico(":/commonIcons/res/imageres.dll(36).ico");
                  ui->cmbdrv->addItem(ico,storage.rootPath().mid(0,2)+"    名称："+storage.name()+"   文件系统类型："+storage.fileSystemType());}
                  else {
                     QIcon ico(":/commonIcons/res/imageres.dll(35).ico");
                     ui->cmbdrv->addItem(ico,storage.rootPath().mid(0,2)+"    名称："+storage.name()+"   文件系统类型："+storage.fileSystemType());
                  }

              }

          }
          else{

              if (storage.rootPath().mid(0,1)=="C"){
              QIcon ico(":/commonIcons/res/imageres.dll(36).ico");
              ui->cmbdrv->addItem(ico,storage.rootPath().mid(0,2)+"    名称："+storage.name()+"   文件系统类型："+storage.fileSystemType());}
              else {
                 QIcon ico(":/commonIcons/res/imageres.dll(35).ico");
                 ui->cmbdrv->addItem(ico,storage.rootPath().mid(0,2)+"    名称："+storage.name()+"   文件系统类型："+storage.fileSystemType());
              }

          }


      }
    }
    ui->cmbdrv->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
    ui->cmbdrv->setCurrentIndex(0);


}
void MainWindow::inicmbdrv()
{
    addcmbdrv();

    QDir d;
    if (d.exists(ui->cmbdrv->currentText().mid(0,1)+":/autorun.inf"))
    {
        QSettings ini(ui->cmbdrv->currentText().mid(0,1)+":/autorun.inf",QSettings::IniFormat);
        ini.beginGroup("Autorun");
       ui->lblico->setScaledContents(1);
       if (!ini.value("ICON").toString().isEmpty())
       {
           ui->txtpath->setText(ini.value("ICON").toString());
           QString str=ini.value("ICON").toString();
           QPixmap  img(ui->cmbdrv->currentText().mid(0,1)+":/"+str);
                   ui->lblico->setPixmap(img);
                   ui->lblico->setVisible(1);
                   ui->lblico->show();



       }
       else {
           ui->lblico->setVisible(0);

       }
        ini.endGroup();

    }
    else {
        ui->lblico->setVisible(0);

    }
}

void MainWindow::setdrvico()
{
    QSettings ini(ui->cmbdrv->currentText().mid(0,2)+"/autorun.inf",QSettings::IniFormat);
    ini.beginGroup("Autorun");
    QImage img(icopth);
    QFile d;

    if (d.exists(icopth))
    {
        QString str=ini.value("ICON").toString();
        if(icopth==ui->cmbdrv->currentText().mid(0,1)+":/"+str)
        {

            ini.setValue("ICON","Driveicon.ico");
            goto l;
//           SetFileAttributes(strFileName,FILE_ATTRIBUTE_HIDDEN);

        }
        QFile::remove(ui->cmbdrv->currentText().mid(0,2)+"/Driveicon.ico");
        if( img.save(ui->cmbdrv->currentText().mid(0,2)+"/Driveicon.ico"))
        {
            ini.setValue("ICON","Driveicon.ico");
               l:

            /*
            LPCWSTR lpautorunpth;
            LPCWSTR lpicopth;
            QString fn=":\autorun.inf";
           QString autorunpth="D:\1.txt";

            std::wstring wlpautorunpth = autorunpth.toStdWString();
             lpautorunpth= wlpautorunpth.c_str();
               SetFileAttributes(lpautorunpth,FILE_ATTRIBUTE_HIDDEN);
               qDebug()<<autorunpth;
            //SetFileAttributesA()
*/

            if (ini.value("ICON").toString()=="Driveicon.ico")
            {
            QMessageBox msg;
            msg.setWindowTitle("成功");
           msg.setIcon(QMessageBox::Information);
           msg.setText("设置成功！重新启动计算机后立即生效!");

           msg.addButton("立即重启",QMessageBox::AcceptRole);
           msg.addButton("稍后重启",QMessageBox::RejectRole);

             if(msg.exec()==QMessageBox::AcceptRole)
             {
                 system("shutdown.exe /r /t 00");
             }
            }
            else
            {
               QMessageBox::critical(this,"失败","设置失败！杀毒软件可能导致了操作失败，请关闭杀毒软件后重试","确定");
            }
        }

        else{
            QMessageBox::critical(this,"失败","设置失败！请检查磁盘是否可以写入。","确定");
        }

    }
    else {
        QMessageBox::critical(this,"失败","设置失败！请检查指定图标是否存在。","确定");
    }
}



//槽函数定义处：
void MainWindow::slot_cmbdrv_currentTextChanged()

{
    ui->txtpath->setText("");
    icopth="";
    QDir d;
    if (d.exists(ui->cmbdrv->currentText().mid(0,1)+":/autorun.inf"))
    {
        QSettings ini(ui->cmbdrv->currentText().mid(0,1)+":/autorun.inf",QSettings::IniFormat);
        ini.beginGroup("Autorun");
       ui->lblico->setScaledContents(1);
       if (!ini.value("ICON").toString().isEmpty())
       {
           ui->txtpath->setText(ini.value("ICON").toString());
       }
        ini.endGroup();
    }



}

void MainWindow::slot_btnapp_clicked()
{
    if(icopth!="")

    {
        QMessageBox::warning(this,"警告","在操作前，请关闭所有杀毒软件，否则可能会失败,即使本软件提示成功。（本软件安全无毒，放心使用）","知道了");
        setdrvico();
        slot_btnref_clicked();
    }
    else {

        QMessageBox::critical(this,"失败","请先选择文件。","确定");
    }
}

void MainWindow::slot_btnref_clicked()
{
    ui->cmbdrv->clear();
    ui->txtpath->clear();
    inicmbdrv();


}

void MainWindow::slot_btndef_clicked()
{
    if(QFile::remove(ui->cmbdrv->currentText().mid(0,1)+":/autorun.inf"))
    {
        QFile::remove(ui->cmbdrv->currentText().mid(0,1)+":/Driveicon.ico");
        slot_btnref_clicked();
        QMessageBox msg;
        msg.setWindowTitle("成功");
       msg.setIcon(QMessageBox::Warning);
       msg.setText("恢复成功！请立即或稍后重启计算机，关机不可以代替重启，否则默认图标无法正常显示！");

       msg.addButton("立即重启",QMessageBox::AcceptRole);
       msg.addButton("稍后重启",QMessageBox::RejectRole);

       if(msg.exec()==QMessageBox::AcceptRole)
       {
           system("shutdown.exe /r /t 00");
       }

    }
    else {
        QMessageBox::critical(this,"失败","恢复失败。","确定");
    }
}

void MainWindow::slot_btnopn_clicked()
{
    icopth=QDir::cleanPath(QFileDialog::getOpenFileName(this,"选择一个图片或图标文件",QDir::currentPath()));
    if(!icopth.isEmpty())
    {
        QFileInfo info(icopth);



        ui->txtpath->setText(info.fileName());

        QPixmap  img(icopth);
                ui->lblico->setPixmap(img);
                ui->lblico->setVisible(1);
                ui->lblico->show();
    }


}

void MainWindow::slot_btnabt_clicked()
{
    AboutWindow *abtwnd=new AboutWindow();
    abtwnd->setVisible(1);
    abtwnd->show();
}

void MainWindow::slot_btnabtus_clicked()
{
    AboutUsWindow *abtwndus=new AboutUsWindow();
    abtwndus->setVisible(1);
    abtwndus->show();
}


void MainWindow::on_cmbdrv_currentTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->txtpath->setText("");

    icopth="";
    QDir d;
    if (d.exists(ui->cmbdrv->currentText().mid(0,1)+":/autorun.inf"))
    {
        QSettings ini(ui->cmbdrv->currentText().mid(0,1)+":/autorun.inf",QSettings::IniFormat);
        ini.beginGroup("Autorun");
       ui->lblico->setScaledContents(1);

       if (!ini.value("ICON").toString().isEmpty())
       {
           ui->txtpath->setText(ini.value("ICON").toString());
           QString str=ini.value("ICON").toString();
//           QMessageBox::information(this,"image:"+ui->cmbdrv->currentText().mid(0,1)+":/"+str,"image:url("+ui->cmbdrv->currentText().mid(0,1)+":/"+str+")");
//         ui->lblico->setStyleSheet("background-image:"+ui->cmbdrv->currentText().mid(0,1)+":/"+str);
         QPixmap  img(ui->cmbdrv->currentText().mid(0,1)+":/"+str);
                 ui->lblico->setPixmap(img);
                 ui->lblico->setVisible(1);
                 ui->lblico->show();
       }
       else {
           ui->lblico->setVisible(0);

       }
        ini.endGroup();
    }
    else {
        ui->lblico->setVisible(0);
    }
}



void MainWindow::on_btnfeedback_clicked()
{
    QMessageBox::information(this,"反馈","暂不支持应用程序内反馈，您可以加通过QQ私聊(2860245799),进行反馈。","确定");
}

void MainWindow::on_btnabtus_3_clicked()
{
    QMessageBox::information(this,"反馈","该版本为最终版！","确定");
}

void MainWindow::on_commandLinkButton_clicked()
{
    QString str=ui->commandLinkButton->text();
    QProcess *pro = new QProcess;
    pro->start("externApps/Axialis_IconWorkshop_v6.9.1.exe", QStringList("Driveicon.ico"));
     ui->commandLinkButton->setText("正在启动，请稍候…");
    pro->waitForStarted();
    ui->commandLinkButton->setText(str);

}

void MainWindow::on_btnapp_clicked()
{

}
