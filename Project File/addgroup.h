#ifndef ADDGROUP_H
#define ADDGROUP_H

#include <QDialog>

namespace Ui {
class addgroup;
}

class addgroup : public QDialog
{
    Q_OBJECT

public:
    explicit addgroup(QWidget *parent = nullptr, QString i="");
    ~addgroup();

private slots:
    void on_add_clicked();

    void on_Cancel_clicked();

private:
    Ui::addgroup *ui;
     QString id;
};

#endif // ADDGROUP_H
