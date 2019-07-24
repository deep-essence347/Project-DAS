#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QDate>
#include "teacher.h"
#include "group.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

     QSqlDatabase info;
     void connClose() {

         info.close();
         info.removeDatabase(QSqlDatabase::defaultConnection);
     }
     bool connOpen()
     {

         info= QSqlDatabase::addDatabase("QSQLITE") ;
         info.setDatabaseName("C:/ProjDAS/info.db");

         if(!info.open()) {
          qDebug()<<("Not Connected");
          return 0;
         }

         else {
          qDebug()<<("Database Connected");
          return 1;
         }
     }


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_login_clicked();


    void on_EditT_clicked();

private:

    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel*model;
    Teacher *teacher;
    group *Group;

};

#endif // MAINWINDOW_H
