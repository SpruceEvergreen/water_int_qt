#include "dialog.h"
#include "./ui_dialog.h"
#include <QTableWidget>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QString>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowFlags( windowFlags() | Qt::WindowMinimizeButtonHint);
    timer = new QTimer(this);
    time = QTime(0, 0, 0);
    ui->label_4->setText(time.toString("hh:mm:ss"));
    QString label_time;
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_func()));
    ui->startTimerBtn->setEnabled(false);

}

Dialog::~Dialog()
{
    delete ui;
}

// Info messages pop-ups
void timer_over() {
    QMessageBox timer_over_msg;
    timer_over_msg.setWindowTitle("Hey!");
    timer_over_msg.setText("The time is up!\n"
                           "You should probably drink a glass of water!");
    timer_over_msg.setWindowFlags(Qt::WindowStaysOnTopHint);
    timer_over_msg.exec();
}

void empty_timer_warning() {
    QMessageBox empty_timer_msg;
    empty_timer_msg.setWindowTitle("Hey!");
    empty_timer_msg.setText("Time can't be 00:00:00!\n");
    empty_timer_msg.exec();
}

void check_glass_counter(int &counter) {
    QMessageBox enough_msg;

    enough_msg.setWindowTitle("Hey!");
    enough_msg.setText("That's probably enough of water!\n"
                       "You should check with your doctor \nabout"
                       " the right amount for you!");
    if (counter > 8 ) {
        enough_msg.exec();
    }
}


// Timer handling functions
void Dialog::timer_func(){

    ui->label_4->setText(time.toString("hh:mm:ss"));
    time = time.addSecs(-1);
    QString time_str = time.toString();
    if (time_str == "00:00:00") {
        timer->stop();
        ui->startTimerBtn->setEnabled(false);
        ui->doneBtn->setEnabled(true);
        ui->timeEdit->setEnabled(true);
        ui->label_4->setText(time.toString("00:00:00"));
        timer_over();
    }
}


void Dialog::start_timer() {

    if (ui->timeEdit->time().toString() != "00:00:00") {
        time = ui->timeEdit->time();
    }
    timer->start(1000);

    if (timer->isActive()) {
        ui->startTimerBtn->setEnabled(false);
        ui->timeEdit->setTime(QTime::fromString("00:00:00"));
        ui->timeEdit->setEnabled(false);
        ui->doneBtn->setEnabled(false);
    }
}

// Clicked buttons functions
void Dialog::on_startTimerBtn_clicked()
{
    start_timer();
}


void Dialog::on_doneBtn_clicked()
{
    QString label_time = ui->timeEdit->time().toString("hh:mm:ss");
    if (label_time == "00:00:00") {
        empty_timer_warning();
    } else {
        ui->label_4->setText(label_time);
        ui->startTimerBtn->setEnabled(true);
    }
}


void Dialog::on_resetTimerBtn_clicked()
{
    timer->stop();
    time = QTime::fromString("00:00:00");
    ui->label_4->setText("00:00:00");
    label_time = "00:00:00";
    ui->startTimerBtn->setEnabled(false);
    ui->doneBtn->setEnabled(true);
    ui->timeEdit->setEnabled(true);
}

void Dialog::on_addGlassBtn_clicked()
{
    QPixmap water_glass_img(":/dialog/images/waterglass-32.png");
    static int row = 0, column = 0;
    QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(pow(row+1, column+1)));
    newItem->setData(Qt::DecorationRole, water_glass_img);
    ui->tableWidget->setItem(0, counter, newItem);
    counter += 1;
    check_glass_counter(counter);
}

void Dialog::on_resetGlassBtn_clicked()
{
    counter = 0;
    ui->tableWidget->clear();
}





