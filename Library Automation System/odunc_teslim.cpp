
#include "odunc_teslim.h"
#include "ui_odunc_teslim.h"

odunc_teslim::odunc_teslim(QSqlDatabase kutuphane,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::odunc_teslim)
{
    ui->setupUi(this);
    sorgu=new QSqlQuery(kutuphane);
    sorgu2=new QSqlQuery(kutuphane);
    listele();
    listele2();

}

odunc_teslim::~odunc_teslim()
{
    delete ui;
}

void odunc_teslim::listele()
{
    sorgu->prepare("select * from odunc_alinan");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata","Ödünç alınan tablosu çekilirken bir hata oluştu.","Tamam");
        return;
    }
    model= new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView_OduncAlinan->setModel(model);
}

void odunc_teslim::listele2()
{
    sorgu2->prepare("select * from odunc_teslim_edilen");
    if(!sorgu2->exec())
    {
        QMessageBox::critical(this,"Hata","Ödünç teslim edilen kitaplar tablosu çekilirken bir hata oluştu.","Tamam");
        return;
    }
    model2= new QSqlQueryModel();
    model2->setQuery(*sorgu2);
    ui->tableView_OduncTeslimEdilen->setModel(model2);
}

void odunc_teslim::on_tableView_OduncAlinan_clicked(const QModelIndex &index)
{
    ui->lineEdit_UyeNo->setText(model->index(index.row(),0).data().toString());
    ui->lineEdit_KitapNo->setText(model->index(index.row(),1).data().toString());
    alma_tarihi=model->index(index.row(),2).data().toString();
    QList<QString> bilgiler = alma_tarihi.split(".");
    int gun=bilgiler[0].toInt();
    int ay=bilgiler[1].toInt();
    int yil=bilgiler[2].toInt();
    if(ay==1)
    {
        ay=0;
    }
    else if(ay==2)
    {
        ay=31;
    }
    else if(ay==3)
    {
        ay=60;
    }
    else if(ay==4)
    {
        ay=91;
    }
    else if(ay==5)
    {
        ay=121;
    }
    else if(ay==6)
    {
        ay=152;
    }
    else if(ay==7)
    {
        ay=182;
    }
    else if(ay==8)
    {
        ay=213;
    }
    else if(ay==9)
    {
        ay=244;
    }
    else if(ay==10)
    {
        ay=274;
    }
    else if(ay==11)
    {
        ay=305;
    }
    else if(ay==12)
    {
        ay=335;
    }
    alma_sayisi = (yil-1)*365+ay+gun;

}


void odunc_teslim::on_pushButton_oduncVer_clicked()
{
    if(ui->lineEdit_UyeNo->text()==""||ui->lineEdit_KitapNo->text()=="")
    {
        QMessageBox::critical(this,"Hata","Üye ve kitabı seçiniz!","Tamam");
    }
    else
    {

        int borc=0;
        QString verme_tarihi=ui->dateEdit_oduncVer->text();
        QList<QString> bilgiler2 = verme_tarihi.split(".");
        int gun2=bilgiler2[0].toInt();
        int ay2=bilgiler2[1].toInt();
        int yil2=bilgiler2[2].toInt();
        if(ay2==1)
        {
            ay2=0;
        }
        else if(ay2==2)
        {
            ay2=31;
        }
        else if(ay2==3)
        {
            ay2=60;
        }
        else if(ay2==4)
        {
            ay2=91;
        }
        else if(ay2==5)
        {
            ay2=121;
        }
        else if(ay2==6)
        {
            ay2=152;
        }
        else if(ay2==7)
        {
            ay2=182;
        }
        else if(ay2==8)
        {
            ay2=213;
        }
        else if(ay2==9)
        {
            ay2=244;
        }
        else if(ay2==10)
        {
            ay2=274;
        }
        else if(ay2==11)
        {
            ay2=305;
        }
        else if(ay2==12)
        {
            ay2=335;
        }

        int verme_sayisi=(yil2-1)*365+ay2+gun2;
        if(verme_sayisi>=alma_sayisi)
        {
            int gecen_gun = verme_sayisi-alma_sayisi;
            if(gecen_gun>15)
            {
                borc=(gecen_gun-15)*2;
            }
            else{
                borc=0;
            }



            sorgu->prepare("insert into odunc_teslim_edilen(uye_no,kitap_no,alma_tarihi,verme_tarihi,borc) values(?,?,?,?,?)");
            sorgu->addBindValue(ui->lineEdit_UyeNo->text().toInt());
            sorgu->addBindValue(ui->lineEdit_KitapNo->text().toInt());
            sorgu->addBindValue(alma_tarihi);
            sorgu->addBindValue(verme_tarihi);
            sorgu->addBindValue(borc);
            if(!sorgu->exec())
            {
                QMessageBox::critical(this,"Hata","Ödünç verilirken bir hata oluştu.","Tamam");
                return;
            }
            sorgu->prepare("delete from odunc_alinan where uye_no=? and kitap_no=?");
            sorgu->addBindValue(ui->lineEdit_UyeNo->text().toInt());
            sorgu->addBindValue(ui->lineEdit_KitapNo->text().toInt());
            if(!sorgu->exec())
            {
                QMessageBox::critical(this,"Hata","Kitap ödünç alınanlar tablosundan silinirken bir hata oluştu.","Tamam");
                return;
            }
            listele2();
            listele();
            ui->lineEdit_UyeNo->clear();
            ui->lineEdit_KitapNo->clear();
        }
        else{
           QMessageBox::critical(this,"Hata","Teslim tarihi, alım tarihinden önce olamaz","Tamam");
        }

    }
}

