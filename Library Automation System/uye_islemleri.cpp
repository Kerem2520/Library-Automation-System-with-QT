

#include "uye_islemleri.h"
#include "ui_uye_islemleri.h"

uye_islemleri::uye_islemleri(QSqlDatabase kutuphane, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::uye_islemleri)
{
    ui->setupUi(this);
    sorgu=new QSqlQuery(kutuphane);
    sorgu2=new QSqlQuery(kutuphane);
    sorgu3=new QSqlQuery(kutuphane);
    sorgu4=new QSqlQuery(kutuphane);
    listele();
}

uye_islemleri::~uye_islemleri()
{
    delete ui;
}

void uye_islemleri::listele()
{
    sorgu->prepare("select * from uye");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata","Üye tablosu çekilirken bir hata oluştu.","Tamam");
        return;
    }
    model= new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView_uye->setModel(model);
}

void uye_islemleri::on_tableView_uye_clicked(const QModelIndex &index)
{
    ui->lineEdit_uyeNo->setText(model->index(index.row(),0).data().toString());
    ui->lineEdit_uyeAD->setText(model->index(index.row(),1).data().toString());
    ui->lineEdit_uyeSoyad->setText(model->index(index.row(),2).data().toString());

    sorgu3->prepare("select * from odunc_alinan where uye_no=?");
    sorgu3->addBindValue(ui->lineEdit_uyeNo->text().toInt());
    if(!sorgu3->exec())
    {
        QMessageBox::critical(this,"Hata","Üyede olan kitaplar tablosu çekilirken bir hata oluştu.","Tamam");
        return;
    }
    model3= new QSqlQueryModel();
    model3->setQuery(*sorgu3);
    ui->tableView_uyekitaplar->setModel(model3);

    sorgu4->prepare("select * from odunc_teslim_edilen where uye_no=?");
    sorgu4->addBindValue(ui->lineEdit_uyeNo->text().toInt());
    if(!sorgu4->exec())
    {
        QMessageBox::critical(this,"Hata","Üyede önceden olan kitaplar tablosu çekilirken bir hata oluştu.","Tamam");
        return;
    }
    model2= new QSqlQueryModel();
    model2->setQuery(*sorgu4);
    ui->tableView_uyekitaplar_onceden->setModel(model2);
}


void uye_islemleri::on_pushButton_uyeKayit_clicked()
{
    if(ui->lineEdit_uyeAD->text()==""||ui->lineEdit_uyeSoyad->text()=="")
    {
      QMessageBox::critical(this,"Hata","Gerekli alanları doldurunuz!","Tamam");
    }
    else
    {
        sorgu->prepare("insert into uye(uye_ad,uye_soyad) values(?,?)");
        sorgu->addBindValue(ui->lineEdit_uyeAD->text());
        sorgu->addBindValue(ui->lineEdit_uyeSoyad->text());
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata","Üye kaydedilirken bir hata oluştu.","Tamam");
            return;
        }
        listele();
    }

}


void uye_islemleri::on_pushButton_uyeGuncelle_clicked()
{
    if(ui->lineEdit_uyeAD->text()==""||ui->lineEdit_uyeSoyad->text()=="")
    {
        QMessageBox::critical(this,"Hata","Gerekli alanları doldurunuz!","Tamam");
    }
    else
    {
        sorgu->prepare("update uye set uye_ad=?,uye_soyad=? where uye_no=?");
        sorgu->addBindValue(ui->lineEdit_uyeAD->text());
        sorgu->addBindValue(ui->lineEdit_uyeSoyad->text());
        sorgu->addBindValue(ui->lineEdit_uyeNo->text().toInt());
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata","Üye bilgileri güncellenirken bir hata oluştu.","Tamam");
            return;
        }
        listele();
    }

}


void uye_islemleri::on_pushButton_uyeSil_clicked()
{
    sorgu2->prepare("select * from odunc_alinan where uye_no=?");
    sorgu2->addBindValue(ui->lineEdit_uyeNo->text().toInt());
    sorgu2->exec();
    if(sorgu2->next())
    {
        QMessageBox::critical(this,"Hata","Bu üyenin elinde teslim etmediği kitap var,üye silinemez!","Tamam");
        return;
    }
    else
    {
        sorgu->prepare("delete from uye where uye_no=?");
        sorgu->addBindValue(ui->lineEdit_uyeNo->text().toInt());
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata","Üye bilgileri silinirken bir hata oluştu.","Tamam");
            return;
        }
        listele();

    }
}





