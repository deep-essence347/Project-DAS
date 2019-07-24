#include "form.h"
#include "ui_form.h"
#include "teacher.h"
#include "mainwindow.h"
#include<QMessageBox>

Form::Form(QWidget *parent,QString name) :
    QMainWindow(parent),
    ui(new Ui::Form)
{
    tableName=name;
    ui->setupUi(this);
    MainWindow conn;

    if(!conn.connOpen()) {
     qDebug()<<"Not Connected";
    }

    else {
     qDebug()<<"Database Connected";
    }


}

Form::~Form()
{

    delete ui;
}



void Form::on_register_2_clicked()
{
    MainWindow conn;
    QString SID, Name, Roll_No, Stream, Batch;
    SID = ui->sid_i->text();
    Name = ui->name_i ->text();
    Roll_No = ui->roll_no_i ->text();

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into "+tableName+" (SID,Name,Roll_No) values ('"+SID+"','"+Name+"','"+Roll_No+"')");



    if(qry.exec())
    {
        QMessageBox::information(this, tr("Update"),tr("Data Registered Successfully"));
        conn.connClose();
        hide();
    }

    else {
         QMessageBox::critical(this, tr("Error"),qry.lastError().text());
    }

}

void Form::on_update_clicked()
{
    MainWindow conn;
    QString SID, Name, Roll_No;
    SID = ui->sid_i->text();
    Name = ui->name_i ->text();
    Roll_No = ui->roll_no_i ->text();

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("update "+tableName+" set SID='"+SID+"',Name='"+Name+"',Roll_No='"+Roll_No+"' where SID='"+SID+"' ");

    if(qry.exec())
    {
        QMessageBox::information(this, tr("Update"),tr("Data Updated Successfully."));
        conn.connClose();
        hide();
    }

    else {
         QMessageBox::critical(this, tr("Error!"),qry.lastError().text());
    }

}


void Form::on_RemoveStd_clicked()
{
    int warn=QMessageBox::warning(this,tr(""),tr("This information cannot be retrieved.\nAre you sure you want to delete the information? "),QMessageBox::Yes|QMessageBox::No);
    switch(warn)
    {

    case QMessageBox::Yes:

    QString text=ui->LRemove->text();
    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    if(ui->RSid->isChecked())
    {
        qry.prepare("Delete from "+tableName+" where sid="+text+"");
        if(qry.exec())
        {
             QMessageBox::information(this, tr(""),tr("Successfully removed."));
             hide();
        }
        else {
             QMessageBox::information(this, tr("Error!"),tr("Unable to remove. Check your database connection."));
        }
    }
    if(ui->RName->isChecked())
    {
        qry.prepare("Delete from "+tableName+" where name='"+text+"'");
        if(qry.exec())
        {
             QMessageBox::information(this, tr(""),tr("Successfully removed."));
            hide();
        }
        else {
             QMessageBox::information(this, tr("Error!"),tr("Unable to remove. Check your database connection."));
        }
    }
    if(ui->RRoll->isChecked())
    {
        qry.prepare("Delete from "+tableName+" where roll_no="+text+"");
        if(qry.exec())
        {
             QMessageBox::information(this, tr(""),tr("Successfully removed."));
            hide();
        }
        else {
             QMessageBox::information(this, tr("Error!"),tr("Unable to remove. Check your database connection."));
        }
    }
    conn.connClose();
    }
}

void Form::on_CancelF_clicked()
{
    hide();
}
