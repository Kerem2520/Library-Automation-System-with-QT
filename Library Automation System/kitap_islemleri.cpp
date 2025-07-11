
#include "kitap_islemleri.h"
#include "ui_kitap_islemleri.h"

kitap_islemleri::kitap_islemleri(QSqlDatabase kutuphane,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::kitap_islemleri)
{
    ui->setupUi(this);
    sorgu=new QSqlQuery(kutuphane);
    sorgu2=new QSqlQuery(kutuphane);
    sorgu3=new QSqlQuery(kutuphane);
    sorgu4=new QSqlQuery(kutuphane);
    listele();

}

kitap_islemleri::~kitap_islemleri()
{
    delete ui;
}

void kitap_islemleri::listele()
{
    sorgu->prepare("select * from kitap");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata","Kitap tablosu çekilirken bir hata oluştu.","Tamam");
        return;
    }
    model= new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView_tumKitaplar->setModel(model);
}

void kitap_islemleri::on_tableView_tumKitaplar_clicked(const QModelIndex &index)
{
    ui->lineEdit_kitapNo->setText(model->index(index.row(),0).data().toString());
    ui->lineEdit_KitapAd->setText(model->index(index.row(),1).data().toString());
    ui->lineEdit_stok->setText(model->index(index.row(),2).data().toString());

    sorgu2->prepare("select * from odunc_alinan where kitap_no=?");
    sorgu2->addBindValue(ui->lineEdit_kitapNo->text().toInt());
    if(!sorgu2->exec())
    {
        QMessageBox::critical(this,"Hata","Kitabın ödünç alınma durumu tablosu çekilirken bir hata oluştu.","Tamam");
        return;
    }
    model2= new QSqlQueryModel();
    model2->setQuery(*sorgu2);
    ui->tableView_oduncAlinan->setModel(model2);

    sorgu3->prepare("select * from odunc_teslim_edilen where kitap_no=?");
    sorgu3->addBindValue(ui->lineEdit_kitapNo->text().toInt());
    if(!sorgu3->exec())
    {
        QMessageBox::critical(this,"Hata","Kitabın önceden ödünç alınma durumu tablosu çekilirken bir hata oluştu.","Tamam");
        return;
    }
    model3= new QSqlQueryModel();
    model3->setQuery(*sorgu3);
    ui->tableView_oncedenOduncAlinan->setModel(model3);


}


void kitap_islemleri::on_pushButton_KitapKayit_clicked()
{
    if(ui->lineEdit_KitapAd->text()==""||ui->lineEdit_stok->text()=="")
    {
        QMessageBox::critical(this,"Hata","Gerekli alanları doldurunuz!","Tamam");
    }
    else
    {
        sorgu->prepare("insert into kitap(kitap_ad,kitap_sayisi) values(?,?)");
        sorgu->addBindValue(ui->lineEdit_KitapAd->text());
        sorgu->addBindValue(ui->lineEdit_stok->text().toInt());
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata","Kitap kaydedilirken bir hata oluştu.","Tamam");
            return;
        }
        listele();
    }
}


void kitap_islemleri::on_pushButton_KitapGuncelle_clicked()
{
    if(ui->lineEdit_KitapAd->text()==""||ui->lineEdit_stok->text()=="")
    {
        QMessageBox::critical(this,"Hata","Gerekli alanları doldurunuz!","Tamam");
    }
    else
    {
        sorgu->prepare("update kitap set kitap_ad=?,kitap_sayisi=? where kitap_no=?");
        sorgu->addBindValue(ui->lineEdit_KitapAd->text());
        sorgu->addBindValue(ui->lineEdit_stok->text().toInt());
        sorgu->addBindValue(ui->lineEdit_kitapNo->text().toInt());
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata","Kitap bilgileri güncellenirken bir hata oluştu.","Tamam");
            return;
        }
        listele();
    }
}


void kitap_islemleri::on_pushButton_KitapSil_clicked()
{
    sorgu4->prepare("select * from odunc_alinan where kitap_no=?");
    sorgu4->addBindValue(ui->lineEdit_kitapNo->text().toInt());
    sorgu4->exec();
    if(sorgu4->next())
    {
        QMessageBox::critical(this,"Hata","Bu kitap şuan bir üyenin elinde, silinemez!","Tamam");
        return;
    }
    else
    {
        sorgu->prepare("delete from kitap where kitap_no=?");
        sorgu->addBindValue(ui->lineEdit_kitapNo->text().toInt());
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata","Kitap bilgileri silinirken bir hata oluştu.","Tamam");
            return;
        }
        listele();
    }


}

