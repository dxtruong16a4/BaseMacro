#include "settingswindow.h"
#include "ui_settingswindow.h"

std::unique_ptr<SettingsWindow> SettingsWindow::uniqueInstance = nullptr;

SettingsWindow::SettingsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SettingsWindow)
    , configManager(new ConfigManager(SETTINGFILEPATH))
{
    ui->setupUi(this);
    initWidget();
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

SettingsWindow* SettingsWindow::getInstance()
{
    if (!uniqueInstance) {
        uniqueInstance = std::make_unique<SettingsWindow>();
    }
    return uniqueInstance.get();
}

bool SettingsWindow::getReset()
{
    return isReset;
}

void SettingsWindow::setSaveToFalse()
{
    this->isSave = false;
}

void SettingsWindow::setMainWindowOpacity(double opac)
{
    MainWindow* mw = MainWindow::getInstance();
    if (mw) {
        mw->setWindowOpacity(opac);
    }
}

void SettingsWindow::initWidget()
{
    isSave = false;
    ui->cbPinCorner->clear();
    ui->cbPinCorner->addItem("Topleft");
    ui->cbPinCorner->addItem("Topright");
    ui->cbPinCorner->addItem("Bottomleft");
    ui->cbPinCorner->addItem("Bottomright");
    ui->cbPinCorner->setCurrentText(configManager->getPinCorner());
    int opacity = configManager->getOpacity();
    ui->lbOpacity->setText(QStringLiteral("Opacity: ") + QString::number(opacity) + "%");
    ui->sliderOpacity->setValue(opacity);
    ui->checkBoxHide->setChecked(configManager->getHide());
}

void SettingsWindow::closeEvent(QCloseEvent *event)
{
    if (!isSave){
        this->setMainWindowOpacity(configManager->getOpacity() / 100.0);
        this->initWidget();
    }
    uniqueInstance.reset();
    event->accept();
}

void SettingsWindow::on_sliderOpacity_sliderMoved(int position)
{
    ui->lbOpacity->setText(QStringLiteral("Opacity: ") + QString::number(position) + "%");
    this->setMainWindowOpacity(position / 100.0);
}

void SettingsWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        this->close();
    }
}

void SettingsWindow::on_btnResetDefault_clicked()
{
    isReset = true;
}


void SettingsWindow::on_btnSave_clicked()
{
    isSave = true;
    configManager->setPinCorner(ui->cbPinCorner->currentText());
    configManager->setOpacity(ui->sliderOpacity->value());
    configManager->setHide(ui->checkBoxHide->isChecked());
    if (isReset){
        configManager->saveSettings(DWIDTH, DHEIGHT, DPOSX, DPOSY, DPIN, DOPACITY, DHIDE);
    }
}
