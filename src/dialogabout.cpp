#include "dialogabout.h"
#include "ui_dialogabout.h"
#include "DefaultConstants.h"

DialogAbout* DialogAbout::uniqueInstance = nullptr;

DialogAbout::DialogAbout(QWidget *parent)
    : DialogBase(parent)
    , ui(new Ui::DialogAbout)
{
    ui->setupUi(this);
}

DialogAbout::~DialogAbout()
{
    delete ui;
    if (uniqueInstance == this) {
        uniqueInstance = nullptr;
    }
}

DialogAbout* DialogAbout::getInstance()
{
    if (uniqueInstance == nullptr) {
        uniqueInstance = new DialogAbout();
    }
    return uniqueInstance;
}

void DialogAbout::closeEvent(QCloseEvent *event)
{
    this->hide();
    event->ignore();
}

void DialogAbout::on_commandLinkButton_clicked()
{
    QDesktopServices::openUrl(QUrl(MYGITHUBURL));
}
