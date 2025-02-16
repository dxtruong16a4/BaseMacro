#include "dialogabout.h"
#include "ui_dialogabout.h"
#include "../core/DefaultConstants.h"

std::unique_ptr<DialogAbout> DialogAbout::uniqueInstance = nullptr;

DialogAbout::DialogAbout(QWidget *parent)
    : DialogBase(parent)
    , ui(new Ui::DialogAbout)
{
    ui->setupUi(this);
}

DialogAbout::~DialogAbout()
{
    delete ui;
}

DialogAbout* DialogAbout::getInstance()
{
    if (!uniqueInstance) {
        uniqueInstance = std::make_unique<DialogAbout>();
    }
    return uniqueInstance.get();
}

void DialogAbout::closeEvent(QCloseEvent *event)
{
    uniqueInstance.reset();
    event->accept();
}

void DialogAbout::on_commandLinkButton_clicked()
{
    QDesktopServices::openUrl(QUrl(MYGITHUBURL));
}
