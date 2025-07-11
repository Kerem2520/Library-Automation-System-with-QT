
#ifndef KITAP_ISLEMLERI_H
#define KITAP_ISLEMLERI_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlError>

namespace Ui {
class kitap_islemleri;
}

class kitap_islemleri : public QDialog
{
    Q_OBJECT

public:
    explicit kitap_islemleri(QSqlDatabase,QWidget *parent = nullptr);
    ~kitap_islemleri();
    void listele();

private slots:
    void on_tableView_tumKitaplar_clicked(const QModelIndex &index);

    void on_pushButton_KitapKayit_clicked();

    void on_pushButton_KitapGuncelle_clicked();

    void on_pushButton_KitapSil_clicked();

private:
    Ui::kitap_islemleri *ui;
    QSqlQuery *sorgu,*sorgu2,*sorgu3,*sorgu4;
    QSqlQueryModel *model,*model2,*model3;
};

#endif // KITAP_ISLEMLERI_H
