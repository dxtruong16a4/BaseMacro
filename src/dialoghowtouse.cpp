#include "dialoghowtouse.h"
#include "ui_dialoghowtouse.h"

DialogHowToUse* DialogHowToUse::uniqueInstance = nullptr;

DialogHowToUse::DialogHowToUse(QWidget *parent)
    : DialogBase(parent)
    , ui(new Ui::DialogHowToUse)
{
    ui->setupUi(this);
}

DialogHowToUse::~DialogHowToUse()
{
    delete ui;
    if (uniqueInstance == this) {
        uniqueInstance = nullptr;
    }
}

DialogHowToUse* DialogHowToUse::getInstance()
{
    if (uniqueInstance == nullptr) {
        uniqueInstance = new DialogHowToUse();
    }
    return uniqueInstance;
}

void DialogHowToUse::closeEvent(QCloseEvent *event)
{
    this->hide();
    event->ignore();
}
