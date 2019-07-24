#include "take.h"
#include "ui_take.h"
#include <QDate>
#include "mainwindow.h"
#include <QSqlQuery>
#include<QMessageBox>
#include <QDialog>
take::take(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::take)
{
    ui->setupUi(this);

            QDate date=QDate::currentDate();
            QString datetext=date.toString();

            ui->Date->setText(datetext);


            /*MainWindow conn;
            QSqlQueryModel modal;
            conn.connOpen();
            QSqlQuery qry;

            modal.setQuery("Select * from s_info order by roll_no ASC");
                for(int i=0;i<modal.rowCount();i++)
                {
                int roll = modal.record(i).value("roll_no").toInt();
                QString name = modal.record(i).value("name").toString();
                qDebug() << roll << name;
                ui->TRoll->setNum(roll);
                ui->TName->setText(""+name+"");
                }
             conn.connClose();
*/
}
            take::~take()
              {
                  delete ui;
              }
bool take::on_present_clicked()
{

    /*QString roll= ui->TRoll->text();

    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    QSqlTableModel modal;
    qry.prepare("Update s_info set Attendence=Attendence + 1 where roll_no='"+roll+"'");
    qry.exec();
    openTake();
    conn.connClose();*/
    return true;
}

bool take::on_absent_clicked()
{
    //QString roll= ui->TRoll->text();
    //MainWindow conn;
    //conn.connOpen();
    //QSqlQuery qry;
    //qry.prepare("Update s_info set Absent_Days=Absent_Days + 1 where roll_no='"+roll+"'");
    //qry.exec();
    //openTake();
    //conn.connClose();
    return true;
}

bool take::on_leave_clicked()
{
    /*QString roll= ui->TRoll->text();
    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("Update s_info set Absent_Days=Absent_Days + 1, Considered_Days=Considered_Days+1 where roll_no='"+roll+"'");
    qry.exec();
    openTake();
    conn.connClose();*/
    return true;
}
void take::openTake()
{
    hide();
    Take=new take(this);
    Take->show();

}
void take::doTake()
{
    MainWindow conn;
                QSqlQueryModel modal;
                conn.connOpen();
                QSqlQuery qry;

                modal.setQuery("Select * from s_info order by roll_no ASC");
                    //for(int i=0;i<modal.rowCount();i++)
                int i=0;
                if(i<modal.rowCount())
                    {
                    int roll = modal.record(i).value("roll_no").toInt();
                    QString name = modal.record(i).value("name").toString();
                    qDebug() << roll << name<<modal.rowCount();
                    ui->TRoll->setNum(roll);
                    ui->TName->setText(""+name+"");

                    if(on_present_clicked())
                    {
                        QString roll= ui->TRoll->text();
                        qry.prepare("Update s_info set Attendence=Attendence + 1 where roll_no='"+roll+"'");
                        qry.exec();
                        openTake();
                    }
                    if(on_absent_clicked())
                    {
                        QString roll= ui->TRoll->text();
                        qry.prepare("Update s_info set Absent_Days=Absent_Days + 1 where roll_no='"+roll+"'");
                        qry.exec();
                        openTake();
                    }
                    if(on_leave_clicked())
                    {
                        QString roll= ui->TRoll->text();
                        qry.prepare("Update s_info set Absent_Days=Absent_Days + 1 where roll_no='"+roll+"'");
                        qry.exec();
                        openTake();
                    }
                    i++;
                   /* bool x=connect(ui->present,SIGNAL(clicked()),this,SLOT(openTake()));
                    bool y=connect(ui->absent,SIGNAL(clicked()),this,SLOT(openTake()));
                    bool z=connect(ui->leave,SIGNAL(clicked()),this,SLOT(openTake()));

                    if(x==true)
                    {
                        on_present_clicked();
                    }
                    if(y==true)
                    {
                        on_absent_clicked();
                    }
                    if(z==true)
                    {
                        on_leave_clicked();
                    }*/
                    }


                 conn.connClose();
}
