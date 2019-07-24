#ifndef GROUP_H
#define GROUP_H

#include <QDialog>
#include "addgroup.h"
#include "history.h"
#include "teacher.h"
namespace Ui {
class group;
}

class group : public QDialog
{
    Q_OBJECT

public:
    explicit group(QWidget *parent = nullptr,QString idname="");
    ~group();

private slots:
    void on_AddG_clicked();



    void on_RemoveG_clicked();

    void on_refresh_clicked();

    void on_select_clicked();

    void on_Export_clicked();
    bool queryToCsv();
    void on_PHistory_clicked();

    void on_SignOut_clicked();

private:
    Ui::group *ui;
    addgroup *add;
    QString id;
    Teacher *teacher;
    history *History;
};

#endif // GROUP_H
