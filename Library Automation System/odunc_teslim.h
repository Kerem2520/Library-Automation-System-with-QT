

#ifndef ODUNC_TESLIM_H
#define ODUNC_TESLIM_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlError>
#include <QDate>

namespace Ui {
class odunc_teslim;
}

class odunc_teslim : public QDialog
{
    Q_OBJECT

public:
    explicit odunc_teslim(QSqlDatabase,QWidget *parent = nullptr);
    ~odunc_teslim();
    void listele();
    void listele2();
    QString alma_tarihi;
    int alma_sayisi;



private slots:
    void on_tableView_OduncAlinan_clicked(const QModelIndex &index);

    void on_pushButton_oduncVer_clicked();

private:
    Ui::odunc_teslim *ui;
    QSqlQuery *sorgu,*sorgu2;
    QSqlQueryModel *model,*model2;
};

#endif // ODUNC_TESLIM_H
