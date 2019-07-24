#ifndef TEACHER_H
#define TEACHER_H

#include <QMainWindow>
#include "form.h"


#include "take.h"
#include "attendance.h"
namespace Ui {
class Teacher;
}

class Teacher : public QMainWindow
{
    Q_OBJECT

public:
    explicit Teacher(QWidget *parent = nullptr, QString t = "",QString idname="");
    ~Teacher();

private slots:

    void on_view_clicked();

    void on_edit_clicked();

    void on_search_clicked();


    void on_take_clicked();


    void on_backT_clicked();

private:
    Ui::Teacher *ui;

    Form *form;
    Attendance *attendance;

    take *Take;
    QString Name;
    QString id;
    QString TableName;
};

#endif // TEACHER_H
