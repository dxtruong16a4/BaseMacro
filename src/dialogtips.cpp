#include "dialogtips.h"
#include "ui_dialogtips.h"

DialogTips* DialogTips::uniqueInstance = nullptr;

DialogTips::DialogTips(QWidget *parent)
    : DialogBase(parent)
    , ui(new Ui::DialogTips)
{
    ui->setupUi(this);
}

DialogTips::~DialogTips()
{
    delete ui;
    if (uniqueInstance == this) {
        uniqueInstance = nullptr;
    }
}

DialogTips* DialogTips::getInstance()
{
    if (uniqueInstance == nullptr) {
        uniqueInstance = new DialogTips();
    }
    return uniqueInstance;
}

void DialogTips::closeEvent(QCloseEvent *event)
{
    this->hide();
    event->ignore();
}
