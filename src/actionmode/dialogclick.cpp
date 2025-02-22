#include "dialogclick.h"
#include "ui_dialogclick.h"

DialogClick::DialogClick(QWidget *parent)
    : DialogBase(parent)
    , ui(new Ui::DialogClick)
{
    ui->setupUi(this);
    disableWheelWidget();

    connect(ui->cbEventType, &QComboBox::currentIndexChanged, this, &DialogClick::eventTypeChange);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DialogClick::getMousePos);
    timer->start(50);
}

DialogClick::~DialogClick()
{
    delete ui;
}

void DialogClick::closeEvent(QCloseEvent *event)
{
    resetToDefault();
    event->accept();
}

void DialogClick::keyPressEvent(QKeyEvent *event)
{
    QPoint globalPos = QCursor::pos();
    if (event->key() == Qt::Key_F2){
        ui->sbXPos->setValue(globalPos.x());
        ui->sbYPos->setValue(globalPos.y());
    }
    if (event->key() == Qt::Key_F3){
        hideOtherWindow();
    }
}

void DialogClick::editItem(QListWidgetItem *item)
{
    if (!item) return;
    isEditing = true;
    editingItem = item;
    setData(item->text());
    this->show();
}

void DialogClick::eventTypeChange()
{
    int index = ui->cbEventType->currentIndex();
    switch (index) {
    case 0:
    case 1:
        disableWheelWidget();
        enableRepeatWidget();
        ui->chbCurrentPos->setEnabled(true);
        break;
    case 4:
        disableWheelWidget();
        disableRepeatWidget();
        ui->chbCurrentPos->setEnabled(false);
        break;
    case 2:
    case 3:
        enableWheelWidget();
        enableRepeatWidget();
        ui->chbCurrentPos->setEnabled(true);
        break;
    default:
        break;
    }
}

void DialogClick::getMousePos()
{
    QPoint globalPos = QCursor::pos();
    ui->lbXPos->setText(QString::number(globalPos.x()));
    ui->lbYPos->setText(QString::number(globalPos.y()));
}

void DialogClick::on_btnOk_clicked()
{
    MacroEditor *me = MacroEditor::getInstance();
    if (isEditing && editingItem) {
        QString indentation = me->getIndentation(editingItem->text());
        editingItem->setText(indentation + getData());
    } else {
        me->addItemToList(getData());
    }
    me->setIsChanged(true);
    this->close();
    showOtherWindow();
    resetToDefault();
    isEditing = false;
    editingItem = nullptr;
}

void DialogClick::on_btnCancel_clicked()
{
    this->close();
    showOtherWindow();
}

void DialogClick::resetToDefault()
{
    ui->cbEventType->setCurrentIndex(0);
    ui->sbTimes->setValue(1);
    ui->sbMs->setValue(50);
    ui->sbXPos->setValue(0);
    ui->sbYPos->setValue(0);
    ui->chbCurrentPos->setChecked(false);
    ui->sbWheel->setValue(0);
}

void DialogClick::disableWheelWidget()
{
    ui->lbWheel->setEnabled(false);
    ui->sbWheel->setEnabled(false);
    ui->lbWheelValue->setEnabled(false);
}

void DialogClick::enableWheelWidget()
{
    ui->lbWheel->setEnabled(true);
    ui->sbWheel->setEnabled(true);
    ui->lbWheelValue->setEnabled(true);
}

void DialogClick::disableRepeatWidget()
{
    ui->lbTimes->setEnabled(false);
    ui->sbTimes->setEnabled(false);
    ui->lbMs->setEnabled(false);
    ui->sbMs->setEnabled(false);
}

void DialogClick::enableRepeatWidget()
{
    ui->lbTimes->setEnabled(true);
    ui->sbTimes->setEnabled(true);
    ui->lbMs->setEnabled(true);
    ui->sbMs->setEnabled(true);
}

void DialogClick::showOtherWindow()
{
    MacroEditor *me = MacroEditor::getInstance();
    if (me){
        me->show();
    }
    MainWindow *w = MainWindow::getInstance();
    if (w){
        w->show();
    }
}

void DialogClick::hideOtherWindow()
{
    MacroEditor *me = MacroEditor::getInstance();
    if (me){
        me->hide();
    }
    MainWindow *w = MainWindow::getInstance();
    if (w){
        w->hide();
    }
}

/**
 * @brief Parses a command string and updates the UI elements accordingly.
 *
 * @param data The input string must follow one of these formats:
 * - `"MOUSE EVENTTYPEINDEX TIMES MS X Y FLAG 0"`
 * - `"MOUSE EVENTTYPEINDEX TIMES MS X Y FLAG WHEEL"`
 * - `"MOUSE EVENTTYPEINDEX 0 0 X Y 0 0"`
 *
 * @note This function checks `parts.size()` before accessing elements to prevent out-of-bounds errors.
 */
void DialogClick::setData(const QString& data)
{
    QRegularExpression regex(R"(^(\s*)(\S.*)$)");
    QRegularExpressionMatch match = regex.match(data);

    if (!match.hasMatch()) return;

    QString content = match.captured(2);
    QStringList parts = content.split(" ", Qt::SkipEmptyParts);

    if (parts.size() < 8) return;
    bool ok;

    int index = parts[1].toInt(&ok);
    if (ok) ui->cbEventType->setCurrentIndex(index);

    int times = (index == 4) ? 1 : parts[2].toInt(&ok);
    if (ok) ui->sbTimes->setValue(times);

    int ms = (index == 4) ? 50 : parts[3].toInt(&ok);
    if (ok) ui->sbMs->setValue(ms);

    int x = parts[4].toInt(&ok);
    if (ok) ui->sbXPos->setValue(x);

    int y = parts[5].toInt(&ok);
    if (ok) ui->sbYPos->setValue(y);

    int posFlag = (index != 4) ? parts[6].toInt(&ok) : 0;
    if (ok) ui->chbCurrentPos->setChecked(posFlag);

    int wheel = (index == 2 || index == 3) ? parts[7].toInt(&ok) : 0;
    if (ok) ui->sbWheel->setValue(wheel);
}

/**
 * @brief Retrieves mouse action data from the UI and formats it into a command string.
 *
 * The returned string follows these formats:
 * - If `EVENTTYPEINDEX == 0` or `1`: `"MOUSE EVENTTYPEINDEX TIMES MS X Y FLAG 0"`
 * - If `EVENTTYPEINDEX == 2` or `3`: `"MOUSE EVENTTYPEINDEX TIMES MS X Y FLAG WHEEL"`
 * - If `EVENTTYPEINDEX == 4`: `"MOUSE EVENTTYPEINDEX 0 0 X Y 0 0"`
 *
 * @return QString A formatted string representing the mouse action data.
 */
QString DialogClick::getData()
{
    int index = ui->cbEventType->currentIndex();
    int flag = (index != 4) ? ui->chbCurrentPos->isChecked() : 0;
    int wheel = (index == 2 || index == 3) ? ui->sbWheel->value() : 0;

    QString times = (index == 4) ? "0" : ui->sbTimes->text();
    QString ms = (index == 4) ? "0" : ui->sbMs->text();

    QString data = "MOUSE";
    data += " " + QString::number(index);
    data += " " + times;
    data += " " + ms;
    data += " " + ui->sbXPos->text();
    data += " " + ui->sbYPos->text();
    data += " " + QString::number(flag);
    data += " " + QString::number(wheel);

    return data;
}
