#include "dialogtips.h"
#include "ui_dialogtips.h"

std::unique_ptr<DialogTips> DialogTips::uniqueInstance = nullptr;

DialogTips::DialogTips(QWidget *parent)
    : DialogBase(parent)
    , ui(new Ui::DialogTips)
{
    ui->setupUi(this);
}

DialogTips::~DialogTips()
{
    delete ui;
}

DialogTips* DialogTips::getInstance()
{
    if (!uniqueInstance) {
        uniqueInstance = std::make_unique<DialogTips>();
    }
    return uniqueInstance.get();
}

void DialogTips::setData(const QString &data)
{

}

void DialogTips::editItem(QListWidgetItem *item)
{

}

void DialogTips::closeEvent(QCloseEvent *event)
{
    uniqueInstance.reset();
    event->accept();
}
