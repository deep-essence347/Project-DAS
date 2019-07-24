#include "teacher.h"
#include "ui_teacher.h"
#include "form.h"
#include "take.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QMessageBox>
#include<QDialog>
#include "group.h"
Teacher::Teacher(QWidget *parent, QString tableName,QString idname) :
    QMainWindow(parent),
    ui(new Ui::Teacher)
{
    ui->setupUi(this);
    MainWindow conn;
    conn.connOpen();
    Name=tableName;
    id=idname;
    QSqlQuery qry;
    QSqlQueryModel *modal=new QSqlQueryModel();
    QString query="Select * from tableList where tableName='"+Name+"' and ID='"+id+"';";
    modal->setQuery(query);
    QString name=modal->record(0).value("tableName").toString();
    QString year=modal->record(0).value("Year").toString();
    QString sem=modal->record(0).value("Sem").toString();
    TableName="_"+id+name+"_"+year+sem;
    qDebug()<<id;
    qDebug()<<Name;
    qDebug()<<year;
    qDebug()<<sem;
    ui->LGroup->setText(name);
    ui->LYear->setText("Year "+year);
    ui->LSem->setText(sem+" Sem");
    conn.connClose();
}

Teacher::~Teacher()
{
    delete ui;
}


void Teacher::on_view_clicked()
{
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry= new QSqlQuery(conn.info);

    if (TableName != "") {
        qry->prepare("Select *from "+TableName+" order by roll_no");

        qry->exec();
        modal->setQuery(*qry);
        ui-> tableView ->setModel(modal);
    } else {
        QMessageBox::information(this, tr("Error!"), tr("Stream not set."));
    }

    conn.connClose();
    qDebug()<< (modal->rowCount());


}

void Teacher::on_edit_clicked()
{
    //hide();
    form = new Form(this,TableName);
    form->show();

}
void Teacher::on_search_clicked()
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

void Teacher::on_take_clicked()
{

    Attendance *attend=new Attendance(this,TableName);
    attend->show();

}


void Teacher::on_backT_clicked()
{
    hide();
    group *Group=new group(this,id);
    Group->show();
}
