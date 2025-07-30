#include "dialogdelay.h"
#include "ui_dialogdelay.h"
#include "../utils/helper.h"

DialogDelay::DialogDelay(QWidget *parent)
    : DialogBase(parent)
    , ui(new Ui::DialogDelay)
{
    ui->setupUi(this);

    // Initialize the icon for dragging to get the window title
    lbGetWindowTitle = new QLabel(this);
    lbGetWindowTitle->setPixmap(QPixmap(":/resources/icon/location").scaled(32, 32));
    lbGetWindowTitle->setGeometry(400, 220, 32, 32);
    lbGetWindowTitle->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    lbGetWindowTitle->hide();
    lbGetWindowTitle->setEnabled(false);

    ui->tabWidget->setCurrentIndex(0);
    ui->sbTotal->selectAll();

    // Initialize the tracking timer
    trackingTimer = new QTimer(this);
    connect(trackingTimer, &QTimer::timeout, this, &DialogDelay::updateWindowTitle);
}

DialogDelay::~DialogDelay()
{
    trackingTimer->stop();
    delete trackingTimer;
    delete lbGetWindowTitle;
    delete ui;
}

void DialogDelay::closeEvent(QCloseEvent *event)
{
    isEditing = false;
    editingItem = nullptr;
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

void DialogDelay::mousePressEvent(QMouseEvent *event) {
    QPoint labelPosInDialog = lbGetWindowTitle->mapTo(this, QPoint(0, 0));
    QRect labelRect(labelPosInDialog, lbGetWindowTitle->size());
    if (lbGetWindowTitle->isEnabled() && labelRect.contains(event->pos()) && event->button() == Qt::LeftButton) {
        QPixmap pix(":/resources/icon/location");
        QCursor customCursor(pix.scaled(32, 32), 16, 16);
        QApplication::setOverrideCursor(customCursor);
        tracking = true;
        trackingTimer->start(100);
    }
}

void DialogDelay::mouseReleaseEvent(QMouseEvent *event) {
    if (tracking) {
        QApplication::restoreOverrideCursor();
        tracking = false;
        trackingTimer->stop();
        lbGetWindowTitle->move(400, 220);
    }
}

void DialogDelay::on_tabWidget_currentChanged(int index)
{
    switch (index) {
    case 0:
        ui->sbTotal->selectAll();
        lbGetWindowTitle->hide();
        lbGetWindowTitle->setEnabled(false);
        break;
    case 1:
        lbGetWindowTitle->show();
        lbGetWindowTitle->setEnabled(true);
        break;
    case 2:
        lbGetWindowTitle->hide();
        lbGetWindowTitle->setEnabled(false);
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


void DialogDelay::on_rbtnAnyInteract_clicked(bool checked)
{
    if (checked) {
        ui->lbKeyShortcut->setEnabled(false);
        ui->keySequenceEdit->setEnabled(false);
        ui->lbKeyShortcutTip->setEnabled(false);
    } else {
        ui->lbKeyShortcut->setEnabled(true);
        ui->keySequenceEdit->setEnabled(true);
        ui->lbKeyShortcutTip->setEnabled(true);
    }
}

void DialogDelay::on_rbtnSpecificKey_clicked(bool checked)
{
    if (checked) {
        ui->lbKeyShortcut->setEnabled(true);
        ui->keySequenceEdit->setEnabled(true);
        ui->lbKeyShortcutTip->setEnabled(true);
    } else {
        ui->lbKeyShortcut->setEnabled(false);
        ui->keySequenceEdit->setEnabled(false);
        ui->lbKeyShortcutTip->setEnabled(false);
    }
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
        if (ui->tfWindowTitle->text().isEmpty()){
            QMessageBox::warning(this, "Error", "Please enter a window title!");
            return;
        }
        if (ui->sbWindowTimeout->value() == 0) {
            QMessageBox::warning(this, "Error", "Please enter a timeout value greater than 0!");
            return;
        }
        if (ui->sbWindowTimeout->value() < 1000) {
            QMessageBox::warning(this, "Error", "Please enter a timeout value greater than 1000!");
            return;
        }
        break;
    case 2:
        if (ui->sbUserTimeout->value() == 0) {
            QMessageBox::warning(this, "Error", "Please enter a timeout value greater than 0!");
            return;
        }
        if (ui->sbUserTimeout->value() < 1000) {
            QMessageBox::warning(this, "Error", "Please enter a timeout value greater than 1000!");
            return;
        }
        if (ui->rbtnSpecificKey->isChecked() && ui->keySequenceEdit->keySequence().isEmpty()) {
            QMessageBox::warning(this, "Error", "Please enter a key sequence!");
            return;
        }
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
    me->setChanged(true);
    this->close();
    resetToDefault();
    isEditing = false;
    editingItem = nullptr;
}

void DialogDelay::on_btnCancel_clicked()
{
    isEditing = false;
    editingItem = nullptr;
    this->close();
}

void DialogDelay::startTracking() {
    trackingTimer->start(100);
    startTrackingDrag(this, lbGetWindowTitle);
    stopTracking();
}

void DialogDelay::updateWindowTitle() {
    ui->tfWindowTitle->setText(getWindowTitle());
}

void DialogDelay::stopTracking() {
    if (trackingTimer->isActive()) {
        trackingTimer->stop();
        updateWindowTitle();
    }
}

void DialogDelay::resetToDefault()
{
    ui->tabWidget->setCurrentIndex(0);
    ui->sbTotal->setValue(1);
    ui->rbtnAppear->setChecked(true);
    ui->tfWindowTitle->setText("");
    ui->sbWindowTimeout->setValue(1000);
    ui->rbtnSpecificKey->setChecked(true);
    ui->keySequenceEdit->setKeySequence(QKeySequence(""));
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
         * For the second tab (index = 1), the data is retrieved from `sbTimeout` and `tfWindowTitle`
         * and returned in the format: "DELAY <index> <appear/disappear> <timeout> <window title>", where appear = 1 and disappear = 0.
         *
         * For the third tab (index = 2), the data is retrieved from `sbUserTimeout`
         * and returned in the format: "DELAY <index> <any interact/particular interact> <keysequence> <timeout>", where any interact = 1 and particular interact = 0.
         *
         * @return QString Data string in the format "DELAY <index> <milliseconds>".
         */
        return data + " " + QString::number(index) + " " + QString::number(ui->sbTotal->value());
        break;
    case 1:
        data += " " + QString::number(index);
        data += ui->rbtnAppear->isChecked() ? " 1" : " 0";
        data += " " + QString::number(ui->sbWindowTimeout->value()) + " " + ui->tfWindowTitle->text();
        return data;
        break;
    case 2:
        data += " " + QString::number(index);
        data += ui->rbtnAnyInteract->isChecked() ? " 1" : " 0";
        data += " " + QString::number(ui->sbUserTimeout->value());
        if (ui->rbtnSpecificKey->isChecked()) {
            data += " " + ui->keySequenceEdit->keySequence().toString();
        } else {
            data += " None";
        }        
        return data;
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
    // Step 1: Get index of delay action tab
    QStringList strA = DialogBase::getContent(data, 3);
    if (strA.size() < 2) return;
    bool ok;

    // Step 2: Get value of delay action tab based on index
    int index = strA[1].toInt(&ok);
    QString newData;
    for (int i = 2; i < strA.size(); i++) {
        newData += strA[i];
    }
    QStringList strB, strC, strD;
    if(ok && index == 0) {
        strB = DialogBase::getContent(newData);
    } else if (ok && index == 1) {
        strC = DialogBase::getContent(newData, 3);
    } else if (ok && index == 2) {
        strD = DialogBase::getContent(newData, 3);
    } else {
        return;
    }

    // Step 3: Set data for the delay action tab based on index
    if (index == 0){
        /**
         * @brief Sets data for the first tab from the input string.
         *
         * If the first tab (index = 0) is selected, the `sbTotal` value will be updated
         * based on the input string. The data must be in the format "DELAY <index> <milliseconds>".
         *
         * If the second tab (index = 1) is selected, the `sbWindowTimeout` and `tfWindowTitle` values will be updated
         * based on the input string. The data must be in the format "DELAY <index> <appear/disappear> <timeout> <window title>".
         *
         * If the third tab (index = 2) is selected, the `sbUserTimeout` value and `keySequenceEdit` will be updated
         * based on the input string. The data must be in the format "DELAY <index> <any interact/particular interact> <keysequence> <timeout>".
         *
         * @param data Input string containing information about the tab and the value to set.
         */
        if (ok) ui->tabWidget->setCurrentIndex(index);
        int milliseconds = strB[0].toInt(&ok);
        if (ok) ui->sbTotal->setValue(milliseconds);
    } else if (index == 1) {
        if (strC.size() < 3) return;
        if (ok) ui->tabWidget->setCurrentIndex(index);
        if (strC[0] == "1") {
            ui->rbtnAppear->setChecked(true);
        } else {
            ui->rbtnDisappear->setChecked(true);
        }
        int timeout = strC[1].toInt(&ok);
        if (ok) ui->sbWindowTimeout->setValue(timeout);\
        QString windowTitle = strC[2];
        if (ok) ui->tfWindowTitle->setText(windowTitle);
    } else if (index == 2) {
        if (ok) ui->tabWidget->setCurrentIndex(index);
        int timeout = strD[1].toInt(&ok);
        if (ok) ui->sbUserTimeout->setValue(timeout);
        if (strD[0] == "1") {
            ui->rbtnAnyInteract->setChecked(true);
            ui->keySequenceEdit->setEnabled(false);
            ui->lbKeyShortcutTip->setEnabled(false);
            ui->lbKeyShortcut->setEnabled(false);
        } else {
            ui->rbtnSpecificKey->setChecked(true);
            QString keySequence = strD[2];
            if (!keySequence.isEmpty()) {
                ui->keySequenceEdit->setKeySequence(QKeySequence(keySequence));
            }
            ui->keySequenceEdit->setEnabled(true);
            ui->lbKeyShortcutTip->setEnabled(true);
            ui->lbKeyShortcut->setEnabled(true);
        }
    } else {
        return;
    }
}

