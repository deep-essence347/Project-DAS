#ifndef FORM_H
#define FORM_H

#include <QMainWindow>
//#include "teacher.h"
//#include "mainwindow.h"

namespace Ui {
class Form;
}

class Form : public QMainWindow
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr,QString n="");
    ~Form();

private slots:

    void on_register_2_clicked();

    void on_update_clicked();

    void on_RemoveStd_clicked();

    void on_CancelF_clicked();

private:
    Ui::Form *ui;
    QString tableName;
};

#endif // FORM_H
