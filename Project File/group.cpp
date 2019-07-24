#include "group.h"
#include "ui_group.h"
#include <QSqlQuery>
#include<QMessageBox>
#include <QDebug>
#include "mainwindow.h"
#include<QDialog>
group::group(QWidget *parent,QString idname) :
    QDialog(parent),
    ui(new Ui::group)
{
    ui->setupUi(this);
    id=idname;
    qDebug()<<id;
   MainWindow conn;
   QSqlQueryModel *modal = new QSqlQueryModel;
   conn.connOpen();
   QSqlQuery *q = new QSqlQuery(conn.info);
   q->prepare("Select * from tableList where ID=\"" + id+ "\";");
   q->exec();
   modal->setQuery(*q);
   for(int i=0;i<modal->rowCount();i++)
   {
        QString name = modal->record(i).value("tableName").toString();
        QString Year=modal->record(i).value("Year").toString();
        QString sem=modal->record(i).value("Sem").toString();
        ui->Group->addItem(name+"_"+Year+sem);
   }
   conn.connClose();

}


group::~group()
{
    delete ui;
}

void group::on_AddG_clicked()
{
    add=new addgroup(this,id);
    add->show();
    qDebug()<<id;
}


void group::on_RemoveG_clicked()
{
    QString name=ui->Group->currentText();
    if(name!="")
    {
    int button=QMessageBox::warning(this,tr(""),tr("Are you sure you want to remove the group?"),QMessageBox::Yes | QMessageBox::No);
    switch (button) {
    case QMessageBox::Yes:

    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;

    QSqlQueryModel *modal=new QSqlQueryModel();
    modal->setQuery("Select * from tableList where ID=\"" + id+ "\";");
    for(int i=0;i<modal->rowCount();i++)
    {
    QString gName=modal->record(i).value("tableName").toString();
    QString id=modal->record(i).value("ID").toString();
    QString year=modal->record(i).value("Year").toString();
    QString sem=modal->record(i).value("Sem").toString();


        if(name==gName+"_"+year+sem)
        {
            qDebug()<<gName;
            qDebug()<<year;
            qDebug()<<sem;
            QString query="Delete from tableList where tableName=\"" +gName+"\" and Year=\""+year+"\" and Sem=\""+sem+"\"";


            if(!qry.exec(query))
            {
                    QMessageBox::information(this,tr("Error!"),tr("Database Table not deleted."));
        }
            else{
                QMessageBox::information(this,tr(""),tr("Database Table deleted."));
            }

            query = "INSERT INTO DeletedTables(tableName,ID,Year,Sem) VALUES(\""+ gName + "\",\""+ id + "\",\""+year+"\",\""+sem+"\");";
            qDebug() << query;
            if (qry.exec(query)) {
                qDebug() << "Recorded.";
            } else {
                qDebug() << "Could not record.";
            }


        }
    }
    conn.connClose();
    }
    }
    else {
        QMessageBox::information(this,tr(""),tr("Group unspecified."));
    }
}
void group::on_refresh_clicked()
{
    ui->Group->clear();
    MainWindow conn;
    QSqlQueryModel *modal = new QSqlQueryModel;
    conn.connOpen();
    QSqlQuery *q = new QSqlQuery(conn.info);
    q->prepare("Select * from tableList where ID=\"" + id+ "\";");
    q->exec();
    modal->setQuery(*q);
    for(int i=0;i<modal->rowCount();i++)
    {
         QString name = modal->record(i).value("tableName").toString();
         QString Year=modal->record(i).value("Year").toString();
         QString sem=modal->record(i).value("Sem").toString();
         qDebug() << name;
         ui->Group->addItem(name+"_"+Year+sem);
    }
    conn.connClose();
}

void group::on_select_clicked()
{
    MainWindow conn;
    conn.connOpen();
    QString name=ui->Group->currentText();
    qDebug()<<name;
    if(name!="")
    {
        QSqlQueryModel *modal=new QSqlQueryModel();
        modal->setQuery("Select * from tableList where ID=\"" + id+ "\";");
        for(int i=0;i<modal->rowCount();i++)
        {
        QString gName=modal->record(i).value("tableName").toString();
        QString id=modal->record(i).value("ID").toString();
        QString year=modal->record(i).value("Year").toString();
        QString sem=modal->record(i).value("Sem").toString();

            if(name==gName+"_"+year+sem)
            {
                teacher = new Teacher(this,gName,id);
                teacher->show();
                hide();
                break;
            }
        }

    }
    else {
        QMessageBox::information(this,tr(""),tr("No group selected."));
    }
    conn.connClose();
}
QString escapedCSV(QString unexc)
{
    if (!unexc.contains(QLatin1Char(',')))
        return unexc;
    return '\"' + unexc.replace(QLatin1Char('\"'), QStringLiteral("\"\"")) + '\"';
}

bool group:: queryToCsv()
{
    QString tablename=ui->Group->currentText();
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry= new QSqlQuery(conn.info);

    qry->prepare("Select Name,Roll_No,Present_Days,Absent_Days,Working_Days from _"+id+tablename+" order by roll_no");

    qry->exec();
    modal->setQuery(*qry);
    QFile csvFile("C:/ProjDAS/Exported Files/exported_"+id+tablename+".csv");
    if (!csvFile.open(QFile::WriteOnly | QFile::Text)){
        qDebug("Failed to open csv file");
    }
    QSqlRecord r;
    QTextStream writer(&csvFile);
    QStringList t;
    t << "Name" << "Roll No." << "Present_Days"<<"Absent_Days"<<"Working_Days";
    writer << t.join(',')+"\n";
    t.clear();
    for (int i = 0; i < modal->rowCount(); i++) {
        r = modal->record(i);
        t << r.value(0).toString() << r.value(1).toString() << r.value(2).toString()<< r.value(3).toString()<< r.value(4).toString();
        writer << t.join(',') + "\n";
        t.clear();
    }

    csvFile.close();
    return true;
 }

void group::on_Export_clicked()
{
    QString name=ui->Group->currentText();
    if(name!="")
    {
        if(!queryToCsv())
        {
            QMessageBox::information(this,tr("Error!"),tr("Database File Not Exported."));
        }
        else {
            QMessageBox::information(this,tr(""),tr("Database File Exported."));
        }
    }
    else {
        QMessageBox::information(this,tr(""),tr("No group selected."));
    }

}

void group::on_PHistory_clicked()
{
    History=new history(this,id);
    History->show();
}

void group::on_SignOut_clicked()
{
    hide();
    MainWindow *login;
    login=new MainWindow(this);
    login->show();
}
