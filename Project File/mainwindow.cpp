#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "teacher.h"
#include "form.h"
#include "group.h"
#include "editeach.h"
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    db.open();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_login_clicked()
{
    QString username = ui->Lusername ->text();
    QString password = ui->Lpassword ->text();

    connOpen();
    QSqlQuery qry;
    qry.prepare("Select * from t_info where Username ='"+username+"' and Password = '"+password+"' ");
    QSqlQueryModel modal;


    if(qry.exec())
    {

            int count=0;

            while (qry.next()) {
                count++;
            }

            if (count==1){
                modal.setQuery("Select * from t_info where Username ='"+username+"' and Password = '"+password+"' ");
                QString id=modal.record(0).value("ID").toString();
                qDebug()<<id;
                connClose();
                hide();
                Group= new group (this,id);
                Group->show();

            }
            else {
                QMessageBox::warning(this, tr("Error!"),tr("Incorrect Username or Password."));
            }
    }



}





void MainWindow::on_EditT_clicked()
{
    EdiTeach* edit=new EdiTeach(this);
    edit->show();
}
