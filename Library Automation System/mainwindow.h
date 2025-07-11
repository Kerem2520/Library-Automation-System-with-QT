

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlError>
#include <uye_islemleri.h>
#include <kitap_islemleri.h>
#include <odunc_alma.h>
#include <odunc_teslim.h>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase kutuphane = QSqlDatabase::addDatabase("QSQLITE");
};
#endif // MAINWINDOW_H
