#include "macroeditor.h"
#include "ui_macroeditor.h"
#include <QDebug>

std::unique_ptr<MacroEditor> MacroEditor::uniqueInstance = nullptr;

MacroEditor::MacroEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MacroEditor)
{
    ui->setupUi(this);
    setIsChanged(false);
    connect(ui->listMacro, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(checkAnyChange(QListWidgetItem*)));
}

MacroEditor::~MacroEditor()
{
    DialogPool::instance().releaseAllDialogs();
    delete ui;
}

void MacroEditor::setIsChanged(bool changed)
{
    isChanged = changed;
}

void MacroEditor::addItemToList(QString item)
{
    QList<QListWidgetItem *> selectedItems = ui->listMacro->selectedItems();
    if (selectedItems.isEmpty()) {
        ui->listMacro->addItem(item);
        return;
    }
    int maxRow = -1;
    for (QListWidgetItem *selectedItem : selectedItems) {
        int row = ui->listMacro->row(selectedItem);
        if (row > maxRow) {
            maxRow = row;
        }
    }
    ui->listMacro->insertItem(maxRow + 1, item);
}

/**
 * @brief Extracts the leading whitespace (indentation) from a given string.
 *
 * This function returns the leading spaces or tabs at the beginning of the input text.
 * It is useful for preserving indentation when editing macro items.
 *
 * @param text The input string from which to extract indentation.
 * @return A QString containing the leading whitespace (indentation) of the input text.
 */
QString MacroEditor::getIndentation(const QString &text)
{
    if (text.isEmpty()) return "";

    QRegularExpression regex(R"(^(\s*))");
    QRegularExpressionMatch match = regex.match(text);

    return match.hasMatch() ? match.captured(1) : "";
}

MacroEditor *MacroEditor::getInstance()
{
    if (!uniqueInstance) {
        uniqueInstance = std::make_unique<MacroEditor>();
    }
    return uniqueInstance.get();
}

void MacroEditor::checkAnyChange(QListWidgetItem *item)
{
    Q_UNUSED(item);
    isChanged = true;
}

void MacroEditor::closeEvent(QCloseEvent *event)
{
    if (isChanged) {
        QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Macro Editor",
                                                                   "Do you want to save changes?",
                                                                   QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                   QMessageBox::Yes);
        if (resBtn == QMessageBox::Yes) {
            Save();
            uniqueInstance.reset();
            event->accept();
        } else if (resBtn == QMessageBox::Cancel) {
            event->ignore();
        } else {
            uniqueInstance.reset();
            event->accept();
        }
    } else {
        uniqueInstance.reset();
        event->accept();
    }
}

void MacroEditor::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Right) {
        ChangeIndentLevelUp();
        setIsChanged(true);
        event->accept();
    } else if (event->key() == Qt::Key_Left){
        ChangeIndentLevelDown();
        setIsChanged(true);
        event->accept();
    } else {
        QWidget::keyPressEvent(event);
    }
}

void MacroEditor::New()
{
    if (isChanged) {
        QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Macro Editor",
                                                                   "Do you want to save changes before creating a new macro?",
                                                                   QMessageBox::No | QMessageBox::Yes | QMessageBox::Cancel,
                                                                   QMessageBox::Yes);
        if (resBtn == QMessageBox::Yes) {
            Save();
        } else if (resBtn == QMessageBox::Cancel) {
            return;
        }
    }

    ui->listMacro->clear();
    currentFilePath.clear();
    setIsChanged(false);
}

void MacroEditor::Open()
{
    if (isChanged) {
        QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Macro Editor",
                                                                   "Do you want to save changes before opening a new file?",
                                                                   QMessageBox::No | QMessageBox::Yes | QMessageBox::Cancel,
                                                                   QMessageBox::Yes);
        if (resBtn == QMessageBox::Yes) {
            Save();
        } else if (resBtn == QMessageBox::Cancel) {
            return;
        }
    }

    QString filePath = QFileDialog::getOpenFileName(this, "Select file macro", "", "NTR Files (*.ntr)");
    if (filePath.isEmpty()) return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open file!");
        return;
    }

    QTextStream in(&file);
    ui->listMacro->clear();
    while (!in.atEnd()) {
        QString line = in.readLine();
        ui->listMacro->addItem(line);
    }
    file.close();

    currentFilePath = filePath;
    setIsChanged(false);
}

void MacroEditor::Save()
{
    if (currentFilePath.isEmpty()) {
        SaveAs();
    } else {
        QFile file(currentFilePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "Cannot save file!");
            return;
        }
        QTextStream out(&file);
        for (int i = 0; i < ui->listMacro->count(); ++i) {
            out << ui->listMacro->item(i)->text() << "\n";
        }
        file.close();
        setIsChanged(false);
    }
}

void MacroEditor::SaveAs()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save macro", "", "NTR Files (*.ntr)");
    if (filePath.isEmpty()) return;

    currentFilePath = filePath;
    Save();
}

void MacroEditor::Cut()
{
    QList<QListWidgetItem*> selectedItems = ui->listMacro->selectedItems();
    if (!selectedItems.isEmpty()) {
        QClipboard *clipboard = QGuiApplication::clipboard();
        QStringList textList;
        for (QListWidgetItem *item : selectedItems) {
            textList << item->text();
        }
        clipboard->setText(textList.join("\n"));
        for (QListWidgetItem *item : selectedItems) {
            delete item;
        }
        setIsChanged(true);
    }
}

void MacroEditor::Copy()
{
    QList<QListWidgetItem*> selectedItems = ui->listMacro->selectedItems();
    if (!selectedItems.isEmpty()) {
        QClipboard *clipboard = QGuiApplication::clipboard();
        QStringList textList;
        for (QListWidgetItem *item : selectedItems) {
            textList << item->text();
        }
        clipboard->setText(textList.join("\n"));
    }
}

void MacroEditor::Paste()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    QString text = clipboard->text();
    if (!text.isEmpty()) {
        ui->listMacro->addItem(text);
        setIsChanged(true);
    }
}

void MacroEditor::Delete()
{
    QList<QListWidgetItem*> selectedItems = ui->listMacro->selectedItems();
    if (!selectedItems.isEmpty()) {
        for (QListWidgetItem *item : selectedItems) {
            delete item;
        }
        setIsChanged(true);
    }
}

void MacroEditor::MoveUp()
{
    QList<QListWidgetItem*> selectedItems = ui->listMacro->selectedItems();
    for (QListWidgetItem *item : selectedItems) {
        int currentRow = ui->listMacro->row(item);
        if (currentRow > 0) {
            ui->listMacro->takeItem(currentRow);
            ui->listMacro->insertItem(currentRow - 1, item);
        }
    }
    setIsChanged(true);
}

void MacroEditor::MoveDown()
{
    QList<QListWidgetItem*> selectedItems = ui->listMacro->selectedItems();
    for (int i = selectedItems.size() - 1; i >= 0; --i) {
        QListWidgetItem *item = selectedItems[i];
        int currentRow = ui->listMacro->row(item);
        if (currentRow < ui->listMacro->count() - 1) {
            ui->listMacro->takeItem(currentRow);
            ui->listMacro->insertItem(currentRow + 1, item);
        }
    }
    setIsChanged(true);
}

void MacroEditor::on_actionNew_triggered()
{
    New();
}

void MacroEditor::on_actionOpen_triggered()
{
    Open();
}

void MacroEditor::on_actionSave_triggered()
{
    Save();
}

void MacroEditor::on_actionSave_As_triggered()
{
    SaveAs();
}

void MacroEditor::on_actionExit_triggered()
{
    this->close();
}

void MacroEditor::on_actionCut_triggered()
{
    Cut();
}

void MacroEditor::on_actionCopy_triggered()
{
    Copy();
}

void MacroEditor::on_actionPaste_triggered()
{
    Paste();
}

void MacroEditor::on_actionDelete_triggered()
{
    Delete();
}

void MacroEditor::on_actionMove_up_triggered()
{
    MoveUp();
}

void MacroEditor::on_actionMove_down_triggered()
{
    MoveDown();
}

void MacroEditor::on_actionHow_to_use_triggered()
{

}

void MacroEditor::on_listMacro_itemDoubleClicked(QListWidgetItem *item)
{
    if (!item) return;

    QString mode = item->text().trimmed().split(" ").first();
    DialogBase *dialog = dynamic_cast<DialogBase*>(getDialogByMode(mode));

    if (dialog) {
        dialog->editItem(item);
    }
}

void MacroEditor::on_btnClick_clicked()
{
    DialogClick *d = DialogPool::instance().acquireDialog<DialogClick>("MOUSE");
    if (d) {
        d->show();
    }
}

void MacroEditor::on_btnKeyboard_clicked()
{
    DialogKeyboard *d = DialogPool::instance().acquireDialog<DialogKeyboard>("KEYBOARD");
    if (d) {
        d->show();
    }
}

void MacroEditor::on_btnDelay_clicked()
{
    // show list of dialog pool
    // DialogPool::instance().showPool();
}

void MacroEditor::on_btnPaste_clicked()
{

}

void MacroEditor::on_btnOpenLink_clicked()
{

}

void MacroEditor::on_btnFind_clicked()
{

}

void MacroEditor::on_btnIf_clicked()
{

}

void MacroEditor::on_btnLoop_clicked()
{

}

void MacroEditor::on_btnBracket_clicked()
{

}

void MacroEditor::on_btnLabel_clicked()
{

}

void MacroEditor::on_btnGoto_clicked()
{

}

void MacroEditor::on_btnBreak_Continue_clicked()
{

}

void MacroEditor::on_btnStop_clicked()
{

}

void MacroEditor::on_btnCode_clicked()
{

}

void MacroEditor::ChangeIndentLevelUp()
{
    QList<QListWidgetItem *> selectedItems = ui->listMacro->selectedItems();
    if (!selectedItems.isEmpty()){
        for (QListWidgetItem *selectedItem : selectedItems){
            QString text = selectedItem->text();

            int spaceCount = 0;
            while (spaceCount < text.length() && text[spaceCount] == ' ') {
                spaceCount++;
            }

            int newSpaceCount = spaceCount + 4;
            QString newText = QString(" ").repeated(newSpaceCount) + text.trimmed();

            selectedItem->setText(newText);
        }
    }
    setIsChanged(true);
}

void MacroEditor::ChangeIndentLevelDown()
{
    QList<QListWidgetItem *> selectedItems = ui->listMacro->selectedItems();
    if (!selectedItems.isEmpty()){
        for (QListWidgetItem *selectedItem : selectedItems){
            QString text = selectedItem->text();

            int spaceCount = 0;
            while (spaceCount < text.length() && text[spaceCount] == ' ') {
                spaceCount++;
            }

            int newSpaceCount = qMax(0, spaceCount - 4);
            QString newText = QString(" ").repeated(newSpaceCount) + text.trimmed();

            selectedItem->setText(newText);
        }
    }
    setIsChanged(true);
}

DialogBase *MacroEditor::getDialogByMode(const QString &mode)
{
    if (mode == "MOUSE") {
        return DialogPool::instance().acquireDialog<DialogClick>("MOUSE");
    }
    if (mode == "KEYBOARD") {
        return DialogPool::instance().acquireDialog<DialogKeyboard>("KEYBOARD");
    }
    // Thêm các loại dialog khác tại đây nếu cần
    return nullptr;
}
