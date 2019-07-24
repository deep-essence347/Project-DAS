#ifndef INSIDEHIST_H
#define INSIDEHIST_H

#include <QDialog>
#include <QStandardItemModel>
namespace Ui {
class insideHist;
}

class insideHist : public QDialog
{
    Q_OBJECT

public:
    explicit insideHist(QWidget *parent = nullptr,QString gName="");
    ~insideHist();

private slots:
    void on_search_clicked();

    void on_BackIH_clicked();

    void on_refreshH_clicked();

private:
    Ui::insideHist *ui;
     QStandardItemModel *csvModel;
    QString DelGroup;
    QString TableName;
    QString id;
};

#endif // INSIDEHIST_H
