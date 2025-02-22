#include "dialogabout.h"
#include "ui_dialogabout.h"

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

void DialogAbout::setData(const QString &data)
{

}

void DialogAbout::editItem(QListWidgetItem *item)
{

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
