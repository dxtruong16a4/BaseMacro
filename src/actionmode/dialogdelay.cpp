#include "dialogdelay.h"
#include "ui_dialogdelay.h"

DialogDelay::DialogDelay(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogDelay)
{
    ui->setupUi(this);
}

DialogDelay::~DialogDelay()
{
    delete ui;
}

void DialogDelay::on_sbTotal_valueChanged(int arg1)
{

}

void DialogDelay::on_sbMinutes_valueChanged(int arg1)
{

}

void DialogDelay::on_sbSeconds_valueChanged(int arg1)
{

}

void DialogDelay::on_sbMiliseconds_textChanged(const QString &arg1)
{

}
