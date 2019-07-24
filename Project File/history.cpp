#include "history.h"
#include "ui_history.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include "group.h"
#include<QMessageBox>
history::history(QWidget *parent,QString idname) :
    QDialog(parent),
    ui(new Ui::history)
{
    ui->setupUi(this);
    id=idname;
    MainWindow conn;
    QSqlQueryModel *modal = new QSqlQueryModel;
    conn.connOpen();
    QSqlQuery *q = new QSqlQuery(conn.info);
    q->prepare("Select * from DeletedTables where ID=\"" + id+ "\";");
    q->exec();
    modal->setQuery(*q);
    for(int i=0;i<modal->rowCount();i++)
    {
         QString name = modal->record(i).value("tableName").toString();
         QString Year=modal->record(i).value("Year").toString();
         QString sem=modal->record(i).value("Sem").toString();
         qDebug() << name;
         ui->Histcom->addItem(name+"_"+Year+sem);
    }

    conn.connClose();
}

history::~history()
{
    delete ui;
}

void history::on_HSelect_clicked()
{
    MainWindow conn;
    conn.connOpen();
    QString name=ui->Histcom->currentText();
    qDebug()<<name;
    if(name!="")
    {
        QSqlQueryModel *modal=new QSqlQueryModel();
        modal->setQuery("Select * from DeletedTables where ID=\"" + id+ "\";");
        for(int i=0;i<modal->rowCount();i++)
        {
        QString gName=modal->record(i).value("tableName").toString();
        QString id=modal->record(i).value("ID").toString();
        QString year=modal->record(i).value("Year").toString();
        QString sem=modal->record(i).value("Sem").toString();

            if(name==gName+"_"+year+sem)
            {
                inHistory=new insideHist(this,gName);
                inHistory->show();

                hide();
                break;
            }
        }

}
}

void history::on_BackH_clicked()
{
    hide();
    group *Group=new group(this,id);
    Group->show();
}

QString escCSV(QString unexc)
{
    if (!unexc.contains(QLatin1Char(',')))
        return unexc;
    return '\"' + unexc.replace(QLatin1Char('\"'), QStringLiteral("\"\"")) + '\"';
}

bool history:: queryToCsv()
{
    QString tablename=ui->Histcom->currentText();
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry= new QSqlQuery(conn.info);

    qry->prepare("Select Name,Roll_No,Present_Days,Absent_Days,Working_Days from _"+id+tablename+" order by roll_no");

    qry->exec();
    modal->setQuery(*qry);
    QFile csvFile("C:/ProjDAS/Exported Files/exportedHistory_"+id+tablename+".csv");
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

void history::on_ExportH_clicked()
{
    QString name=ui->Histcom->currentText();
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
