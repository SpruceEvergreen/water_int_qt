#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_addGlassBtn_clicked();

    void on_resetGlassBtn_clicked();

    void on_startTimerBtn_clicked();

    void timer_func();

    void on_resetTimerBtn_clicked();

    void on_doneBtn_clicked();

private:
    Ui::Dialog *ui;
    QTimer *timer;
    QTime time;
    QString label_time;
    int counter = 0;
    void count_down(int &count);
    void start_timer();

};
#endif // DIALOG_H
