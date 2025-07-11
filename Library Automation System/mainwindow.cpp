

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    kutuphane.setDatabaseName("Kutuphane.db");
    if(!kutuphane.open())
    {
        ui->statusbar->showMessage("Veri Tabanına Bağlanılamadı!");
    }
    else
    {
        ui->statusbar->showMessage("Veri Tabanına Bağlanıldı!");
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    uye_islemleri *uye = new uye_islemleri(kutuphane,this);
    uye->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    kitap_islemleri *kitap = new kitap_islemleri(kutuphane,this);
    kitap->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    odunc_alma *odunc = new odunc_alma(kutuphane,this);
    odunc->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    odunc_teslim *teslim = new odunc_teslim(kutuphane,this);
    teslim->show();
}

