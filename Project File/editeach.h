#ifndef EDITEACH_H
#define EDITEACH_H

#include <QDialog>

namespace Ui {
class EdiTeach;
}

class EdiTeach : public QDialog
{
    Q_OBJECT

public:
    explicit EdiTeach(QWidget *parent = nullptr);
    ~EdiTeach();

private slots:
    void on_AddT_clicked();

    void on_RemT_clicked();

    void on_CancelT_clicked();

private:
    Ui::EdiTeach *ui;
};

#endif // EDITEACH_H
