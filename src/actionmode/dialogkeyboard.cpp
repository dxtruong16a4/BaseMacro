#include "dialogkeyboard.h"
#include "ui_dialogkeyboard.h"
#include <QDebug>

DialogKeyboard::DialogKeyboard(QWidget *parent)
    : DialogBase(parent)
    , ui(new Ui::DialogKeyboard)
{
    ui->setupUi(this);
    keyMap = {
        {Qt::Key_Backspace              , "Back"},
        {Qt::Key_Tab                    , "Tab"},
        {Qt::Key_Clear                  , "Clear"},
        {Qt::Key_Return                 , "Enter"},
        {Qt::Key_Shift                  , "LShift"},
        {Qt::Key_Shift                  , "RShift"},
        {Qt::Key_Control                , "LControl"},
        {Qt::Key_Control                , "RControl"},
        {Qt::Key_Alt                    , "LAlt"},
        {Qt::Key_Alt                    , "RAlt"},
        {Qt::Key_Menu                   , "Menu"},
        {Qt::Key_Pause                  , "Pause"},
        {Qt::Key_CapsLock               , "Capital"},
        {Qt::Key_Escape                 , "Escape"},
        {Qt::Key_Space                  , "Space"},
        {Qt::Key_PageUp                 , "Page UP"},
        {Qt::Key_PageDown               , "Page DOWN"},
        {Qt::Key_End                    , "End"},
        {Qt::Key_Home                   , "Home"},
        {Qt::Key_Left                   , "Left"},
        {Qt::Key_Up                     , "Up"},
        {Qt::Key_Right                  , "Right"},
        {Qt::Key_Down                   , "Down"},
        {Qt::Key_Select                 , "Select"},
        {Qt::Key_Print                  , "Print"},
        {Qt::Key_Execute                , "Execute"},
        {Qt::Key_SysReq                 , "Snapshot"},
        {Qt::Key_Insert                 , "Insert"},
        {Qt::Key_Delete                 , "Delete"},
        {Qt::Key_Help                   , "Help"},
        {Qt::Key_0                      , "D0"},
        {Qt::Key_1                      , "D1"},
        {Qt::Key_2                      , "D2"},
        {Qt::Key_3                      , "D3"},
        {Qt::Key_4                      , "D4"},
        {Qt::Key_5                      , "D5"},
        {Qt::Key_6                      , "D6"},
        {Qt::Key_7                      , "D7"},
        {Qt::Key_8                      , "D8"},
        {Qt::Key_9                      , "D9"},
        {Qt::Key_A                      , "A"},
        {Qt::Key_B                      , "B"},
        {Qt::Key_C                      , "C"},
        {Qt::Key_D                      , "D"},
        {Qt::Key_E                      , "E"},
        {Qt::Key_F                      , "F"},
        {Qt::Key_G                      , "G"},
        {Qt::Key_H                      , "H"},
        {Qt::Key_I                      , "I"},
        {Qt::Key_J                      , "J"},
        {Qt::Key_K                      , "K"},
        {Qt::Key_L                      , "L"},
        {Qt::Key_M                      , "M"},
        {Qt::Key_N                      , "N"},
        {Qt::Key_O                      , "O"},
        {Qt::Key_P                      , "P"},
        {Qt::Key_Q                      , "Q"},
        {Qt::Key_R                      , "R"},
        {Qt::Key_S                      , "S"},
        {Qt::Key_T                      , "T"},
        {Qt::Key_U                      , "U"},
        {Qt::Key_V                      , "V"},
        {Qt::Key_W                      , "W"},
        {Qt::Key_X                      , "X"},
        {Qt::Key_Y                      , "Y"},
        {Qt::Key_Z                      , "Z"},
        {Qt::Key_Meta                   , "LWindow"},
        {Qt::Key_Meta                   , "RWindow"},
        // {Qt::Key_0 + Qt::KeypadModifier , "Numpad0"},
        // {Qt::Key_1 + Qt::KeypadModifier , "Numpad1"},
        // {Qt::Key_2 + Qt::KeypadModifier , "Numpad2"},
        // {Qt::Key_3 + Qt::KeypadModifier , "Numpad3"},
        // {Qt::Key_4 + Qt::KeypadModifier , "Numpad4"},
        // {Qt::Key_5 + Qt::KeypadModifier , "Numpad5"},
        // {Qt::Key_6 + Qt::KeypadModifier , "Numpad6"},
        // {Qt::Key_7 + Qt::KeypadModifier , "Numpad7"},
        // {Qt::Key_8 + Qt::KeypadModifier , "Numpad8"},
        // {Qt::Key_9 + Qt::KeypadModifier , "Numpad9"},
        {Qt::Key_Asterisk               , "Multiply"},
        {Qt::Key_Plus                   , "Add"},
        {Qt::Key_Comma                  , "Separator"},
        {Qt::Key_Minus                  , "Subtract"},
        {Qt::Key_Period                 , "Decimal"},
        {Qt::Key_Slash                  , "Divide"},
        {Qt::Key_F1                     , "F1"},
        {Qt::Key_F2                     , "F2"},
        {Qt::Key_F3                     , "F3"},
        {Qt::Key_F4                     , "F4"},
        {Qt::Key_F5                     , "F5"},
        {Qt::Key_F6                     , "F6"},
        {Qt::Key_F7                     , "F7"},
        {Qt::Key_F8                     , "F8"},
        {Qt::Key_F9                     , "F9"},
        {Qt::Key_F10                    , "F10"},
        {Qt::Key_F11                    , "F11"},
        {Qt::Key_F12                    , "F12"},
        {Qt::Key_F13                    , "F13"},
        {Qt::Key_F14                    , "F14"},
        {Qt::Key_F15                    , "F15"},
        {Qt::Key_F16                    , "F16"},
        {Qt::Key_F17                    , "F17"},
        {Qt::Key_F18                    , "F18"},
        {Qt::Key_F19                    , "F19"},
        {Qt::Key_F20                    , "F20"},
        {Qt::Key_F21                    , "F21"},
        {Qt::Key_F22                    , "F22"},
        {Qt::Key_F23                    , "F23"},
        {Qt::Key_F24                    , "F24"},
        {Qt::Key_NumLock                , "Numlock"},
        {Qt::Key_ScrollLock             , "Scroll"}
    }; // Never used
    connect(ui->cbKeyEventType, SIGNAL(currentIndexChanged(int)), this, SLOT(eventTypeChange()));

}

DialogKeyboard::~DialogKeyboard()
{
    delete ui;
}

void DialogKeyboard::closeEvent(QCloseEvent *event)
{
    resetToDefault();
    event->accept();
}

void DialogKeyboard::editItem(QListWidgetItem *item)
{
    if (!item) return;
    isEditing = true;
    editingItem = item;
    setData(item->text());
    this->show();
}

void DialogKeyboard::eventTypeChange()
{
    int index = ui->cbKeyEventType->currentIndex();
    switch (index) {
    case 0:
    case 1:
        disableCombinationWidget();
        disableRepeatWidget();
        break;
    case 2:
        disableCombinationWidget();
        enableRepeatWidget();
        break;
    case 3:
        enableCombinationWidget();
        enableRepeatWidget();
        break;
    default:
        break;
    }
}

void DialogKeyboard::on_btnOk_clicked()
{
    QString selectedKey = ui->cbKey->currentText();
    QMap<QString, QCheckBox*> specialKeys = {
        {"LControl", ui->chbCtrl}, {"RControl", ui->chbCtrl},
        {"LShift", ui->chbShift}, {"RShift", ui->chbShift},
        {"LAlt", ui->chbAlt}, {"RAlt", ui->chbAlt}, {"Menu", ui->chbAlt},
        {"LWindow", ui->chbWin}, {"RWindow", ui->chbWin}
    };
    if (specialKeys.contains(selectedKey) && specialKeys[selectedKey]->isChecked()) {
        QMessageBox::warning(this, "Invalid Selection",
                             "The selected key conflicts with a modifier key. "
                             "Please choose another key.");
        return;
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

void DialogKeyboard::on_btnCancel_clicked()
{
    this->close();
}

void DialogKeyboard::resetToDefault()
{
    ui->cbKeyEventType->setCurrentIndex(2);
    ui->cbKey->setCurrentIndex(40);
    ui->chbCtrl->setChecked(false);
    ui->chbShift->setChecked(false);
    ui->chbAlt->setChecked(false);
    ui->chbWin->setChecked(false);
    ui->sbTimes->setValue(1);
    ui->sbMs->setValue(50);
}

void DialogKeyboard::disableCombinationWidget()
{
    ui->chbCtrl->setEnabled(false);
    ui->chbShift->setEnabled(false);
    ui->chbAlt->setEnabled(false);
    ui->chbWin->setEnabled(false);
}

void DialogKeyboard::enableCombinationWidget()
{
    ui->chbCtrl->setEnabled(true);
    ui->chbShift->setEnabled(true);
    ui->chbAlt->setEnabled(true);
    ui->chbWin->setEnabled(true);
}

void DialogKeyboard::disableRepeatWidget()
{
    ui->sbTimes->setEnabled(false);
    ui->lbTimes->setEnabled(false);
    ui->sbMs->setEnabled(false);
    ui->lbMs->setEnabled(false);
}

void DialogKeyboard::enableRepeatWidget()
{
    ui->sbTimes->setEnabled(true);
    ui->lbTimes->setEnabled(true);
    ui->sbMs->setEnabled(true);
    ui->lbMs->setEnabled(true);
}

/**
 * @brief Retrieves keyboard action data from the UI and formats it into a command string.
 *
 * The returned string follows these formats:
 * - If `KEYEVENTTYPEINDEX == 0` or `1`:
 *   `"KEYBOARD KEYEVENTTYPEINDEX KEYINDEX 0 0 0 0 0 0"`
 * - If `KEYEVENTTYPEINDEX == 2`:
 *   `"KEYBOARD KEYEVENTTYPEINDEX KEYINDEX 0 0 0 0 TIMES MS"`
 * - If `KEYEVENTTYPEINDEX == 3`:
 *   `"KEYBOARD KEYEVENTTYPEINDEX KEYINDEX CTRL SHIFT ALT WIN TIMES MS"`
 *
 * @return QString A formatted string representing the keyboard action data.
 */
QString DialogKeyboard::getData()
{
    QString data = "KEYBOARD";
    int keyEventType = ui->cbKeyEventType->currentIndex();
    int keyIndex = ui->cbKey->currentIndex();
    data += " " + QString::number(keyEventType);
    data += " " + QString::number(keyIndex);
    if (keyEventType == 0 || keyEventType == 1) {
        data += " 0 0 0 0 0 0";
    }
    else if (keyEventType == 2) {
        data += " 0 0 0 0";
        data += " " + ui->sbTimes->text();
        data += " " + ui->sbMs->text();
    }
    else if (keyEventType == 3) {
        data += " " + QString::number(ui->chbCtrl->isChecked());
        data += " " + QString::number(ui->chbShift->isChecked());
        data += " " + QString::number(ui->chbAlt->isChecked());
        data += " " + QString::number(ui->chbWin->isChecked());
        data += " " + ui->sbTimes->text();
        data += " " + ui->sbMs->text();
    }
    return data;
}

/**
 * @brief Parses a command string and updates the UI elements accordingly.
 *
 * @param data The input string must follow one of these formats:
 * - If `KEYEVENTTYPEINDEX == 0` or `1`:
 *   `"KEYBOARD KEYEVENTTYPEINDEX KEYINDEX 0 0 0 0 0 0"`
 * - If `KEYEVENTTYPEINDEX == 2`:
 *   `"KEYBOARD KEYEVENTTYPEINDEX KEYINDEX 0 0 0 0 TIMES MS"`
 * - If `KEYEVENTTYPEINDEX == 3`:
 *   `"KEYBOARD KEYEVENTTYPEINDEX KEYINDEX CTRL SHIFT ALT WIN TIMES MS"`
 *
 * @note This function checks `parts.size()` before accessing elements to prevent out-of-bounds errors.
 */
void DialogKeyboard::setData(const QString &data)
{
    QRegularExpression regex(R"(^(\s*)(\S.*)$)");
    QRegularExpressionMatch match = regex.match(data);

    if (!match.hasMatch()) return;

    QString content = match.captured(2);
    QStringList parts = content.split(" ", Qt::SkipEmptyParts);

    if (parts.size() < 4) return;

    bool ok;
    int keyEventType = parts[1].toInt(&ok);
    if (ok) ui->cbKeyEventType->setCurrentIndex(keyEventType);

    int idkey = parts[2].toInt(&ok);
    if (ok) ui->cbKey->setCurrentIndex(idkey);

    if (keyEventType == 0 || keyEventType == 1) {
        if (parts.size() < 8) return;
        ui->chbCtrl->setChecked(parts[3].toInt(&ok) && ok);
        ui->chbShift->setChecked(parts[4].toInt(&ok) && ok);
        ui->chbAlt->setChecked(parts[5].toInt(&ok) && ok);
        ui->chbWin->setChecked(parts[6].toInt(&ok) && ok);
    }
    else if (keyEventType == 2) {
        if (parts.size() < 9) return;
        ui->chbCtrl->setChecked(false);
        ui->chbShift->setChecked(false);
        ui->chbAlt->setChecked(false);
        ui->chbWin->setChecked(false);
        ui->sbTimes->setValue(parts[7].toInt(&ok) && ok ? parts[7].toInt() : 0);
        ui->sbMs->setValue(parts[8].toInt(&ok) && ok ? parts[8].toInt() : 0);
    }
    else if (keyEventType == 3) {
        if (parts.size() < 9) return;
        ui->chbCtrl->setChecked(parts[3].toInt(&ok) && ok);
        ui->chbShift->setChecked(parts[4].toInt(&ok) && ok);
        ui->chbAlt->setChecked(parts[5].toInt(&ok) && ok);
        ui->chbWin->setChecked(parts[6].toInt(&ok) && ok);
        ui->sbTimes->setValue(parts[7].toInt(&ok) && ok ? parts[7].toInt() : 0);
        ui->sbMs->setValue(parts[8].toInt(&ok) && ok ? parts[8].toInt() : 0);
    }
}

