#include "dialogabout.h"
#include "ui_dialogabout.h"

std::unique_ptr<DialogAbout> DialogAbout::uniqueInstance = nullptr;

DialogAbout::DialogAbout(QWidget *parent)
    : DialogBase(parent)
    , ui(new Ui::DialogAbout)
{
    ui->setupUi(this);
    ui->lbAbout_2->setText(ABOUT);
}

DialogAbout* DialogAbout::getInstance()
{
    if (!uniqueInstance) {
        uniqueInstance = std::make_unique<DialogAbout>();
    }
    return uniqueInstance.get();
}

DialogAbout::~DialogAbout()
{
    delete ui;
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

void DialogAbout::editItem(QListWidgetItem *item)
{

}

void DialogAbout::setData(const QString &data)
{

}
