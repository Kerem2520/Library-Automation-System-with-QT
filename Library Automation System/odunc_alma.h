

#ifndef ODUNC_ALMA_H
#define ODUNC_ALMA_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlError>

namespace Ui {
class odunc_alma;
}

class odunc_alma : public QDialog
{
    Q_OBJECT

public:
    explicit odunc_alma(QSqlDatabase,QWidget *parent = nullptr);
    ~odunc_alma();
    void listele();
    void listele2();

private slots:
    void on_tableView_Tum_Uyeler_clicked(const QModelIndex &index);

    void on_tableView_Tum_Kitaplar_clicked(const QModelIndex &index);

    void on_pushButton_oduncAl_clicked();

private:
    Ui::odunc_alma *ui;
    QSqlQuery *sorgu,*sorgu2,*sorgu3,*sorgu4,*sorgu5,*sorgu6;
    QSqlQueryModel *model,*model2,*model3;
};

#endif // ODUNC_ALMA_H
