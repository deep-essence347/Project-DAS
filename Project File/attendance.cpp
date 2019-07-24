#include "attendance.h"
#include "ui_attendance.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSql>
#include <QFileInfo>
#include "mainwindow.h"
Attendance::Attendance(QWidget *parent,QString name) :
    QDialog(parent),
    ui(new Ui::Attendance)
{

    ui->setupUi(this);
    tableName=name;
    qDebug()<<tableName;



}
Attendance::~Attendance()
{
    delete ui;
}

void Attendance::on_PresentP_clicked()
{
    i=i+1;
    QAbstractItemModel *model = ui->tableView->model();
        ui->tableView->selectRow(i);
        ui->tableView->setFocus();
        QModelIndex index = model->index(i-1,1);
        QString roll= (index.data().toString());

        MainWindow conn;
        conn.connOpen();
        QSqlQuery qry;

        qry.prepare("Update "+tableName+" set Present_Days=Present_Days + 1 where Roll_No='"+roll+"'");
        qry.exec();
        lastindex();
        conn.connClose();
}

void Attendance::on_AbsentP_clicked()
{
    i=i+1;
    QStringList list;
        QAbstractItemModel *model = ui->tableView->model();
        ui->tableView->selectRow(i);
        ui->tableView->setFocus();
        QModelIndex index = model->index(i-1,1);
        QString roll= (index.data().toString());

            MainWindow conn;
            conn.connOpen();
            QSqlQuery qry;
            qry.prepare("Update "+tableName+" set Absent_Days=Absent_Days + 1 where Roll_No='"+roll+"'");
            qry.exec();
            lastindex();
            conn.connClose();
}

void Attendance::on_ConsiderP_clicked()
{
    i=i+1;
    QStringList list;
        QAbstractItemModel *model = ui->tableView->model();
        ui->tableView->selectRow(i);
        ui->tableView->setFocus();
        QModelIndex index = model->index(i-1,1);
        QString roll= (index.data().toString());

            MainWindow conn;
            conn.connOpen();
            QSqlQuery qry;
            qry.prepare("Update "+tableName+" set Absent_Days=Absent_Days + 1, Considered_Days=Considered_Days+1 where Roll_No='"+roll+"'");
            qry.exec();
            lastindex();
            conn.connClose();
}


void Attendance::on_view_clicked()
{
    MainWindow conn;
        QSqlQueryModel * modal = new QSqlQueryModel();

        conn.connOpen();
        QSqlQuery* qry= new QSqlQuery(conn.info);
        qry->prepare("Select Name,Roll_No from "+tableName+" order by Roll_no");
        qry->exec();

        modal->setQuery(*qry);
        ui-> tableView ->setModel(modal);
        ui->tableView-> setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView->selectRow(0);
        ui->tableView->setFocus();

        QSqlQuery query;
        query.prepare("update "+tableName+" set Working_Days=Working_Days + 1");
        query.exec();

        conn.connClose();
        qDebug()<< (modal->rowCount());
}
void Attendance::lastindex()
{
    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    QAbstractItemModel *model = ui->tableView->model();
    ui->tableView->selectRow(i);
    ui->tableView->setFocus();
    QModelIndex index = model->index(i,1);
    QString roll= (index.data().toString());

    QSqlQueryModel *m=new QSqlQueryModel();
    qry.prepare("Select * from "+tableName+" order by roll_no desc limit 1");
    m->setQuery(qry);
    QString last=m->record(0).value("roll_no").toString();

    if(roll==last)
    {
        hide();
    }
    conn.connClose();
}
