#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <QDialog>

namespace Ui {
class Attendance;
}

class Attendance : public QDialog
{
    Q_OBJECT

public:
    explicit Attendance(QWidget *parent = nullptr,QString name="");
    ~Attendance();

private slots:

    void on_PresentP_clicked();

    void on_AbsentP_clicked();

    void on_ConsiderP_clicked();

    void on_view_clicked();
    void lastindex();
private:
    Ui::Attendance *ui;
    QString tableName;
    int i=0;

};

#endif // ATTENDANCE_H
