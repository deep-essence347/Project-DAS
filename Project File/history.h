#ifndef HISTORY_H
#define HISTORY_H

#include <QDialog>
#include "insidehist.h"
namespace Ui {
class history;
}

class history : public QDialog
{
    Q_OBJECT

public:
    explicit history(QWidget *parent = nullptr,QString name="");
    ~history();

private slots:
    void on_HSelect_clicked();

    void on_BackH_clicked();

    void on_ExportH_clicked();

    bool queryToCsv();

private:
    Ui::history *ui;
    insideHist *inHistory;
    QString id;
};

#endif // HISTORY_H
