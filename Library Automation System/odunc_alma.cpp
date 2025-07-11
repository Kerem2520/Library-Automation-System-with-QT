

#include "odunc_alma.h"
#include "ui_odunc_alma.h"

odunc_alma::odunc_alma(QSqlDatabase kutuphane,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::odunc_alma)
{
    ui->setupUi(this);
    sorgu=new QSqlQuery(kutuphane);
    sorgu2=new QSqlQuery(kutuphane);
    sorgu3=new QSqlQuery(kutuphane);
    sorgu4=new QSqlQuery(kutuphane);
    sorgu5=new QSqlQuery(kutuphane);
    sorgu6=new QSqlQuery(kutuphane);
    listele();
    listele2();
}

odunc_alma::~odunc_alma()
{
    delete ui;
}

void odunc_alma::listele()
{
    sorgu->prepare("select * from uye");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata","Üye tablosu çekilirken bir hata oluştu.","Tamam");
        return;
    }
    model= new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView_Tum_Uyeler->setModel(model);

    sorgu3->prepare("select * from kitap");
    if(!sorgu3->exec())
    {
        QMessageBox::critical(this,"Hata","Kitap tablosu çekilirken bir hata oluştu.","Tamam");
        return;
    }
    model3= new QSqlQueryModel();
    model3->setQuery(*sorgu3);
    ui->tableView_Tum_Kitaplar->setModel(model3);
}

void odunc_alma::listele2()
{
    sorgu2->prepare("select * from odunc_alinan");
    if(!sorgu2->exec())
    {
        QMessageBox::critical(this,"Hata","Ödünç alınan tablosu çekilirken bir hata oluştu.","Tamam");
        return;
    }
    model2= new QSqlQueryModel();
    model2->setQuery(*sorgu2);
    ui->tableView_Odunc_Alinan_Kitaplar->setModel(model2);

}

void odunc_alma::on_tableView_Tum_Uyeler_clicked(const QModelIndex &index)
{
    ui->lineEdit_uyeNo->setText(model->index(index.row(),0).data().toString());
}


void odunc_alma::on_tableView_Tum_Kitaplar_clicked(const QModelIndex &index)
{
     ui->lineEdit_KitapNo->setText(model->index(index.row(),0).data().toString());
}


void odunc_alma::on_pushButton_oduncAl_clicked()
{
    if(ui->lineEdit_uyeNo->text()==""||ui->lineEdit_KitapNo->text()=="")
    {
        QMessageBox::critical(this,"Hata","Üye ve kitabı seçiniz!","Tamam");
    }
    else
    {
        int kitapNo=0;
        sorgu4->prepare("select * from odunc_alinan where uye_no=?");
        sorgu4->addBindValue(ui->lineEdit_uyeNo->text().toInt());
        sorgu4->exec();
        while (sorgu4->next())
        {
                kitapNo = sorgu4->value("kitap_no").toInt();
                if(kitapNo==ui->lineEdit_KitapNo->text().toInt())
                {
                    QMessageBox::critical(this,"Hata","Bu üye kitabın bir tanesini zaten ödünç almış. Şuan tekrar verilemez.","Tamam");
                    return;
                }
        }
        int kitapstok=0;
        sorgu6->prepare("select * from kitap where kitap_no=?");
        sorgu6->addBindValue(ui->lineEdit_KitapNo->text().toInt());
        sorgu6->exec();
        while (sorgu6->next())
        {
            kitapstok=sorgu6->value("kitap_sayisi").toInt();
        }


        sorgu5->prepare("select * from odunc_alinan where kitap_no=?");
        sorgu5->addBindValue(ui->lineEdit_KitapNo->text().toInt());
        sorgu5->exec();
        int syc=0;
        while(sorgu5->next())
        {
            syc++;
        }
        if(syc>=kitapstok)
        {
            QMessageBox::critical(this,"Hata","Bu kitaptan stokta kalmamış.","Tamam");
            return;
        }
        else
        {
            sorgu->prepare("insert into odunc_alinan(uye_no,kitap_no,odunc_alma_tarihi) values(?,?,?)");
            sorgu->addBindValue(ui->lineEdit_uyeNo->text().toInt());
            sorgu->addBindValue(ui->lineEdit_KitapNo->text().toInt());
            sorgu->addBindValue(ui->dateEdit->text());
            if(!sorgu->exec())
            {
                QMessageBox::critical(this,"Hata","Ödünç alınırken bir hata oluştu.","Tamam");
                return;
            }
            listele2();
        }
    }
}
/*
sorgu5->prepare("select * from odunc_alinan where kitap_no=?");
sorgu5->addBindValue(ui->lineEdit_KitapNo->text().toInt());
sorgu5->exec();
if(sorgu5->next())
{
    kontrol2=1;
}
if(kontrol1==1 && kontrol2==1)
{
    QMessageBox::critical(this,"Hata","Bu üye kitabın bir tanesini zaten ödünç almış. Şuan tekrar verilemez.","Tamam");
    return;
} */
