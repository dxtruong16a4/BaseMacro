#include "dialogdelay.h"
#include "ui_dialogdelay.h"

DialogDelay::DialogDelay(QWidget *parent)
    : DialogBase(parent)
    , ui(new Ui::DialogDelay)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    ui->sbTotal->selectAll();
}

DialogDelay::~DialogDelay()
{
    delete ui;
}

void DialogDelay::closeEvent(QCloseEvent *event)
{
    resetToDefault();
    event->accept();
}

void DialogDelay::keyPressEvent(QKeyEvent *event)
{
    int index = ui->tabWidget->currentIndex();
    if (event->key() == Qt::Key_Tab) {
        index += 1;
        if (index > 2) {
            index = 0;
        }
        ui->tabWidget->setCurrentIndex(index);
    }
    event->accept();
}

void DialogDelay::on_tabWidget_currentChanged(int index)
{
    switch (index) {
    case 0:
        ui->sbTotal->selectAll();
        break;
    case 1:
        break;
    case 2:
        break;
    default:
        break;
    }
}

void DialogDelay::on_sbTotal_valueChanged(int arg1)
{
    ui->sbMinutes->blockSignals(true);
    ui->sbSeconds->blockSignals(true);
    ui->sbMilliseconds->blockSignals(true);

    int min = arg1 / 60000;
    int seconds = (arg1 % 60000) / 1000;
    int milliseconds = arg1 % 1000;

    ui->sbMinutes->setValue(min);
    ui->sbSeconds->setValue(seconds);
    ui->sbMilliseconds->setValue(milliseconds);

    ui->sbMinutes->blockSignals(false);
    ui->sbSeconds->blockSignals(false);
    ui->sbMilliseconds->blockSignals(false);
}

void DialogDelay::on_sbMinutes_valueChanged(int arg1)
{
    ui->sbTotal->blockSignals(true);
    ui->sbTotal->setValue(arg1 * 60000 + ui->sbSeconds->value() * 1000 + ui->sbMilliseconds->value());
    ui->sbTotal->blockSignals(false);
}

void DialogDelay::on_sbSeconds_valueChanged(int arg1)
{
    ui->sbTotal->blockSignals(true);
    ui->sbTotal->setValue(ui->sbMinutes->value() * 60000 + arg1 * 1000 + ui->sbMilliseconds->value());
    ui->sbTotal->blockSignals(false);
}

void DialogDelay::on_sbMilliseconds_valueChanged(int arg1)
{
    ui->sbTotal->blockSignals(true);
    ui->sbTotal->setValue(ui->sbMinutes->value() * 60000 + ui->sbSeconds->value() * 1000 + arg1);
    ui->sbTotal->blockSignals(false);
}

void DialogDelay::on_btnOk_clicked()
{
    int index = ui->tabWidget->currentIndex();
    switch (index){
    case 0:
        if (ui->sbTotal->value() == 0) {
            QMessageBox::warning(this, "Error", "Please enter a value greater than 0!");
            return;
        }
        break;
    case 1:
        break;
    case 2:
        break;
    default:
        break;
    }
    MacroEditor *me = MacroEditor::getInstance();
    if (isEditing && editingItem) {
        QString indentation = me->getIndentation(editingItem->text());
        editingItem->setText(indentation + getData());
    } else {
        me->addItemToList(getData());
    }
    me->setIsChanged(true);
    this->close();
    resetToDefault();
    isEditing = false;
    editingItem = nullptr;
}

void DialogDelay::on_btnCancel_clicked()
{
    this->close();
}

void DialogDelay::resetToDefault()
{
    ui->tabWidget->setCurrentIndex(0);
    ui->sbTotal->setValue(0);
}

QString DialogDelay::getData()
{
    QString data = "DELAY";
    int index = ui->tabWidget->currentIndex();
    switch (index) {
    case 0:
        /**
         * @brief Returns data from the current tab as a string.
         *
         * For the first tab (index = 0), the data is retrieved from `sbTotal`
         * and returned in the format: "DELAY <index> <milliseconds>".
         *
         * For the second tab (index = 1) // implement later
         *
         * For the third tab (index = 2) // implement later
         *
         * @return QString Data string in the format "DELAY <index> <milliseconds>".
         */
        return data + " " + QString::number(index) + " " + QString::number(ui->sbTotal->value());
        break;
    case 1:
        // implement later
        return data + " " + QString::number(index) + " 0";
        break;
    case 2:
        // implement later
        return data + " " + QString::number(index) + " 0";
        break;
    default:
        break;
    }
    return data + " 0 0";
}

void DialogDelay::editItem(QListWidgetItem *item)
{
    if (!item) return;
    isEditing = true;
    editingItem = item;
    setData(item->text());
    this->show();
}

void DialogDelay::setData(const QString &data)
{
    QStringList parts = DialogBase::getContent(data);
    if (parts.size() < 3) return;
    bool ok;

    int index = parts[1].toInt(&ok);
    if (index == 0){
        /**
         * @brief Sets data for the first tab from the input string.
         *
         * If the first tab (index = 0) is selected, the `sbTotal` value will be updated
         * based on the input string. The data must be in the format "DELAY <index> <milliseconds>".
         *
         * If the second tab (index = 1) is selected, implement later
         *
         * If the third tab (index = 2) is selected, implement later
         *
         * @param data Input string containing information about the tab and the value to set.
         */
        if (ok) ui->tabWidget->setCurrentIndex(index);
        int milliseconds = parts[2].toInt(&ok);
        if (ok) ui->sbTotal->setValue(milliseconds);
    } else if (index == 1) {
        // implement later
    } else {
        // implement later
    }
}
