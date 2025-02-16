#include "dialoghowtouse.h"
#include "ui_dialoghowtouse.h"

std::unique_ptr<DialogHowToUse> DialogHowToUse::uniqueInstance = nullptr;

DialogHowToUse::DialogHowToUse(QWidget *parent)
    : DialogBase(parent)
    , ui(new Ui::DialogHowToUse)
{
    ui->setupUi(this);
}

DialogHowToUse::~DialogHowToUse()
{
    delete ui;
}

DialogHowToUse* DialogHowToUse::getInstance()
{
    if (!uniqueInstance) {
        uniqueInstance = std::make_unique<DialogHowToUse>();
    }
    return uniqueInstance.get();
}

void DialogHowToUse::closeEvent(QCloseEvent *event)
{
    uniqueInstance.reset();
    event->accept();
}
