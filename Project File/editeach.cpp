#include "editeach.h"
#include "ui_editeach.h"
#include <QSqlQuery>
#include "mainwindow.h"
#include <QMessageBox>
#include<QSqlQueryModel>
EdiTeach::EdiTeach(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EdiTeach)
{
    ui->setupUi(this);
}

EdiTeach::~EdiTeach()
{
    delete ui;
}

void EdiTeach::on_AddT_clicked()
{
    MainWindow conn;
    conn.connOpen();
    QString Name=ui->LName->text();
    QString Username=ui->LUserName->text();
    QString Password=ui->LPassword->text();
    QString Retyped=ui->LRetype->text();
    QSqlQuery qry;
    if(Password==Retyped)
    {
        qry.prepare("Insert into t_info(Name, Username, Password) values('"+Name+"','"+Username+"','"+Password+"');");
        if(!qry.exec())
        {
            QMessageBox::information(this,tr("Error!"),tr("Unable to add the information."));
        }
        else {
            QMessageBox::information(this,tr(""),tr("Data Successfully added."));
            hide();
        }
    }
    else {
        QMessageBox::information(this,tr("Error!"),tr("Your Passwords does not match."));
    }
    conn.connClose();
}


void EdiTeach::on_RemT_clicked()
{
    int warn=QMessageBox::warning(this,tr(""),tr("Are you sure you want to remove the information?"),QMessageBox::Yes|QMessageBox::No);

    switch(warn){
    case QMessageBox::Yes:
    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    QSqlQueryModel modal;
    QString Username=ui->RUsername->text();
    QString Password= ui->RPassword->text();
    modal.setQuery("Select * from t_info where Username='"+Username+"' and Password='"+Password+"'");
    QString id=modal.record(0).value("ID").toString();
    qDebug()<<id;
    qry.prepare("Delete from t_info where Username='"+Username+"' and Password='"+Password+"'");
    if(!qry.exec())
    {
        QMessageBox::information(this,tr("Error!"),tr("Unable to remove the data."));
    }
    else {
        QMessageBox::information(this,tr("Error!"),tr("Successfully removed the account."));
        qry.prepare("Delete from tableList where ID='"+id+"'");
        qry.exec();
        qry.prepare("Delete from DeletedTables where ID='"+id+"'");
        qry.exec();
        hide();
    }
}
}

void EdiTeach::on_CancelT_clicked()
{
    hide();
}
