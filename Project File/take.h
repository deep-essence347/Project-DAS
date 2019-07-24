#ifndef TAKE_H
#define TAKE_H
#include<QDate>
#include <QMainWindow>

namespace Ui {
class take;
}

class take : public QMainWindow
{
    Q_OBJECT

public:
    explicit take(QWidget *parent = nullptr);
    ~take();

private slots:

    bool on_present_clicked();

    bool on_absent_clicked();

    bool on_leave_clicked();
    void openTake();

public:
    void doTake();

private:
    Ui::take *ui;
    take *Take;
};

#endif // TAKE_H
