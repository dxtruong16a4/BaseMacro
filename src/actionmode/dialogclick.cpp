#include "dialogclick.h"
#include "ui_dialogclick.h"
#include "../utils/helper.h"

DialogClick::DialogClick(QWidget *parent)
    : DialogBase(parent)
    , ui(new Ui::DialogClick)
{
    ui->setupUi(this);
    disableWheelWidget();

    // Initialize the icon for dragging to get the window title
    lbGetWindowTitle = new QLabel(this);
    lbGetWindowTitle->setPixmap(QPixmap(":/resources/icon/location").scaled(32, 32));
    lbGetWindowTitle->setGeometry(360, 260, 32, 32);
    lbGetWindowTitle->setAttribute(Qt::WA_TransparentForMouseEvents, false);

    disableFocusWidget();

    // Initialize the tracking timer
    trackingTimer = new QTimer(this);
    connect(trackingTimer, &QTimer::timeout, this, &DialogClick::updateWindowTitle);

    connect(ui->cbEventType, &QComboBox::currentIndexChanged, this, &DialogClick::eventTypeChange);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DialogClick::getMousePos);
    timer->start(50);
}

DialogClick::~DialogClick()
{
    trackingTimer->stop();
    delete trackingTimer;
    delete lbGetWindowTitle;
    delete ui;
}

void DialogClick::closeEvent(QCloseEvent *event)
{
    isEditing = false;
    editingItem = nullptr;
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

void DialogClick::mousePressEvent(QMouseEvent *event) {
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

void DialogClick::mouseReleaseEvent(QMouseEvent *event) {
    if (tracking) {
        QApplication::restoreOverrideCursor();
        tracking = false;
        trackingTimer->stop();
        lbGetWindowTitle->move(360, 260);
    }
}

void DialogClick::eventTypeChange()
{
    int index = ui->cbEventType->currentIndex();
    switch (index) {
    case 0:
    case 1:
        disableWheelWidget();
        enableRepeatWidget();
        ui->chbFocusWindow->setEnabled(true);
        break;
    case 4:
        disableWheelWidget();
        disableRepeatWidget();
        ui->chbFocusWindow->setEnabled(false);
        break;
    case 2:
    case 3:
        enableWheelWidget();
        enableRepeatWidget();
        ui->chbFocusWindow->setEnabled(true);
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

void DialogClick::on_chbFocusWindow_clicked(bool checked)
{
    if (checked) {
        enableFocusWidget();
    }
    else {
        disableFocusWidget();
    }
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
    me->setChanged(true);
    this->close();
    showOtherWindow();
    resetToDefault();
    isEditing = false;
    editingItem = nullptr;
}

void DialogClick::on_btnCancel_clicked()
{
    isEditing = false;
    editingItem = nullptr;
    this->close();
    showOtherWindow();
}

void DialogClick::startTracking() {
    trackingTimer->start(100);
    startTrackingDrag(this, lbGetWindowTitle);
    stopTracking();
}

void DialogClick::updateWindowTitle() {
    ui->tfWindowTitle->setText(getWindowTitle());
}

void DialogClick::stopTracking() {
    if (trackingTimer->isActive()) {
        trackingTimer->stop();
        updateWindowTitle();
    }
}

void DialogClick::resetToDefault()
{
    ui->cbEventType->setCurrentIndex(0);
    ui->sbTimes->setValue(1);
    ui->sbMs->setValue(50);
    ui->sbXPos->setValue(0);
    ui->sbYPos->setValue(0);    
    ui->sbWheel->setValue(0);
    ui->chbFocusWindow->setChecked(false);
    ui->tfWindowTitle->setText("");
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

void DialogClick::disableFocusWidget()
{
    ui->lbWindowTitle->setEnabled(false);
    ui->tfWindowTitle->setEnabled(false);
    lbGetWindowTitle->setEnabled(false);
}

void DialogClick::enableFocusWidget()
{
    ui->lbWindowTitle->setEnabled(true);
    ui->tfWindowTitle->setEnabled(true);
    lbGetWindowTitle->setEnabled(true);
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
 * @brief Retrieves mouse action data from the UI and formats it into a command string.
 *
 * Format:
 * MOUSE EVENTTYPEINDEX TIMES MS X Y WHEEL "WINDOW_TITLE"
 *
 * @return QString A formatted string representing the mouse action data.
 */
QString DialogClick::getData()
{
    int index = ui->cbEventType->currentIndex();
    QString times = (index == 4) ? "0" : ui->sbTimes->text();
    QString ms = (index == 4) ? "0" : ui->sbMs->text();
    int wheel = (index == 2 || index == 3) ? ui->sbWheel->value() : 0;
    QString title = ui->chbFocusWindow->isChecked() ? ui->tfWindowTitle->text() : "None";
    if (title.isEmpty()) {
        title = "None";
    }
    QString data = "MOUSE";
    data += " " + QString::number(index);
    data += " " + times;
    data += " " + ms;
    data += " " + QString::number(ui->sbXPos->value());
    data += " " + QString::number(ui->sbYPos->value());
    data += " " + QString::number(wheel);
    data += " " + title;
    return data;
}

void DialogClick::editItem(QListWidgetItem *item)
{
    if (!item) return;
    isEditing = true;
    editingItem = item;
    setData(item->text());
    this->show();
}

/**
 * @brief Parses and sets the UI elements based on the provided command string.
 *
 * This method extracts data from the input string and updates the corresponding
 * UI elements in the dialog. The input string is expected to follow a specific
 * format with up to 8 parts:
 *
 * Format:
 * MOUSE EVENTTYPEINDEX TIMES MS X Y WHEEL "WINDOW_TITLE"
 *
 * - EVENTTYPEINDEX: The index of the event type (e.g., click, scroll).
 * - TIMES: The number of repetitions for the event (ignored for certain event types).
 * - MS: The delay in milliseconds between repetitions (ignored for certain event types).
 * - X, Y: The coordinates for the mouse action.
 * - WHEEL: The wheel scroll value (used for scroll events).
 * - WINDOW_TITLE: The title of the window to focus on (or "None" if no focus is required).
 *
 * @param data The input command string containing the mouse action data.
 */
void DialogClick::setData(const QString& data)
{
    QStringList parts = DialogBase::getContent(data, 8);
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

    int wheel = (index == 2 || index == 3) ? parts[6].toInt(&ok) : 0;
    if (ok) ui->sbWheel->setValue(wheel);

    QString title = parts[7];
    if (title == "None") {
        ui->chbFocusWindow->setChecked(false);
        disableFocusWidget();
    } else {
        ui->chbFocusWindow->setChecked(true);
        enableFocusWidget();
        ui->tfWindowTitle->setText(title);
    }
}
