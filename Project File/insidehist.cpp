#include "insidehist.h"
#include "ui_insidehist.h"
#include<QDialog>
#include <QSqlQuery>
#include<QDebug>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "mainwindow.h"
#include <QSqlQueryModel>
#include<QSqlQuery>
#include<QMessageBox>
#include "history.h"
insideHist::insideHist(QWidget *parent,QString groupName) :
    QDialog(parent),
    ui(new Ui::insideHist)
{
    ui->setupUi(this);
    hide();
   DelGroup=groupName;
   qDebug()<<DelGroup;
    MainWindow conn;
    conn.connOpen();
   QSqlQuery qry;
   QSqlQueryModel *modal=new QSqlQueryModel();
   QString query="Select * from DeletedTables where tableName='"+DelGroup+"';";
   modal->setQuery(query);
   QString name=modal->record(0).value("tableName").toString();
   QString year=modal->record(0).value("Year").toString();
   QString sem=modal->record(0).value("Sem").toString();
   id=modal->record(0).value("ID").toString();
   TableName="_"+id+name+"_"+year+sem;
   ui->HGroup->setText(name);
   ui->HYear->setText("Year "+year);
   ui->HSem->setText(sem+" Sem");


   if (TableName != "") {
       qry.prepare("Select *from "+TableName+" order by roll_no");

       qry.exec();
       modal->setQuery(qry);
       ui-> tableView ->setModel(modal);
   } else {
       QMessageBox::information(this, tr("Error!"), tr("Stream not set."));
   }

   conn.connClose();
   qDebug()<< (modal->rowCount());
}
insideHist::~insideHist()
{
    delete ui;
     delete csvModel;
}

void insideHist::on_search_clicked()
{
    if(ui->RRoll->isChecked()){
        QString roll=ui->search_edit->text();
        MainWindow conn;
        QSqlQueryModel * modal = new QSqlQueryModel();

        conn.connOpen();
        QSqlQuery* qry= new QSqlQuery(conn.info);
        qry->prepare("Select *from "+TableName+" where Roll_No='"+roll+"' order by roll_no");

        qry->exec();
        modal->setQuery(*qry);
        ui-> tableView ->setModel(modal);

        conn.connClose();
        qDebug()<< (modal->rowCount());
    }
    else
    {

    QString username=ui->search_edit->text();
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry= new QSqlQuery(conn.info);

    qry->prepare("Select *from "+TableName+" where name like'%"+username+"%' order by roll_no");

    qry->exec();
    modal->setQuery(*qry);
    ui-> tableView ->setModel(modal);

    conn.connClose();
    qDebug()<< (modal->rowCount());
}
}

void insideHist::on_BackIH_clicked()
{
    hide();
    history *History=new history(this,id);
    History->show();
}

void insideHist::on_refreshH_clicked()
{
    MainWindow conn;
    conn.connOpen();
   QSqlQuery qry;
   QSqlQueryModel *modal=new QSqlQueryModel();
   QString query="Select * from DeletedTables where tableName='"+DelGroup+"';";
   modal->setQuery(query);
   QString name=modal->record(0).value("tableName").toString();
   QString year=modal->record(0).value("Year").toString();
   QString sem=modal->record(0).value("Sem").toString();
   id=modal->record(0).value("ID").toString();
   TableName="_"+id+name+"_"+year+sem;
   ui->HGroup->setText(name);
   ui->HYear->setText("Year "+year);
   ui->HSem->setText(sem+" Sem");


   if (TableName != "") {
       qry.prepare("Select *from "+TableName+" order by roll_no");

       qry.exec();
       modal->setQuery(qry);
       ui-> tableView ->setModel(modal);
   } else {
       QMessageBox::information(this, tr("Error!"), tr("Stream not set."));
   }

   conn.connClose();
   qDebug()<< (modal->rowCount());
}
