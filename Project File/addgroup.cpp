#include "addgroup.h"
#include "ui_addgroup.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include<QMessageBox>
#include "group.h"
addgroup::addgroup(QWidget *parent,QString idname) :
    QDialog(parent),
    ui(new Ui::addgroup)
{
    ui->setupUi(this);
    id=idname;
    qDebug()<<id;
}

addgroup::~addgroup()
{
    delete ui;
}

void addgroup::on_add_clicked()
{
    QString stream = ui->LStream->text();
    QString batch = ui->LBatch->text();
    QString sem=ui->SemC->currentText();
    QString Year=ui->YearC->currentText();
    QString a = stream + batch;
    QSqlDatabase info;
    info= QSqlDatabase::addDatabase("QSQLITE") ;
    info.setDatabaseName("C:/ProjDAS/info.db");

    if(!info.open()) {
     qDebug()<<("Not Connected");
    }

    else {
     qDebug()<<("Database Connected");
    }
    QSqlQuery qry;
    QString newTableName = "_"+ id + a+"_"+Year+sem;
    QString query="CREATE TABLE " + newTableName + " ("
                  "Name VARCHAR(30) NOT NULL,"
                  "Roll_No INTEGER UNIQUE NOT NULL,"
                  "SID INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT DEFAULT 1819000,"
                  "Present_Days INTEGER DEFAULT 0,"
                  "Absent_Days INTEGER DEFAULT 0,"
                  "Considered_Days INTEGER DEFAULT 0,"
                  "Working_Days INTEGER DEFAULT 0);";
    if(!qry.exec(query))
    {
        QMessageBox::information(this,tr("Error!"),tr("Database creation failed."));
    }
    else {
        QMessageBox::information(this,tr(""),tr("Database created."));
        query = "INSERT INTO tableList(tableName,ID,Year,Sem) VALUES(\"" + a + "\", \""+id+"\",\""+Year+"\",\""+sem+"\");";
        qDebug() << query;
        if (qry.exec(query)) {
            qDebug() << "Recorded.";
        } else {
            qDebug() << "Could not record.";
        }
        hide();
    }

    info.close();
    info.removeDatabase(QSqlDatabase::defaultConnection);

    qDebug()<<newTableName;

}

void addgroup::on_Cancel_clicked()
{
    hide();
}
