
#ifndef UYE_ISLEMLERI_H
#define UYE_ISLEMLERI_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlError>


namespace Ui {
class uye_islemleri;
}

class uye_islemleri : public QDialog
{
    Q_OBJECT

public:
    explicit uye_islemleri(QSqlDatabase,QWidget *parent = nullptr);
    ~uye_islemleri();
    void listele();

private slots:
    void on_tableView_uye_clicked(const QModelIndex &index);

    void on_pushButton_uyeKayit_clicked();

    void on_pushButton_uyeGuncelle_clicked();

    void on_pushButton_uyeSil_clicked();


private:
    Ui::uye_islemleri *ui;
    QSqlQuery *sorgu,*sorgu2,*sorgu3,*sorgu4;
    QSqlQueryModel *model,*model2,*model3;
};

#endif // UYE_ISLEMLERI_H
