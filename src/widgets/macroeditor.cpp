#include "macroeditor.h"
#include "ui_macroeditor.h"

std::unique_ptr<MacroEditor> MacroEditor::uniqueInstance = nullptr;

MacroEditor::MacroEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MacroEditor)
{
    ui->setupUi(this);
    connect(ui->listMacro, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(checkAnyChange(QListWidgetItem*)));
}

MacroEditor::~MacroEditor()
{
    delete ui;
}

MacroEditor *MacroEditor::getInstance()
{
    if (!uniqueInstance) {
        uniqueInstance = std::make_unique<MacroEditor>();
    }
    return uniqueInstance.get();
}

void MacroEditor::closeEvent(QCloseEvent *event)
{
    if (isChange) {
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

void MacroEditor::New()
{
    if (isChange) {
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
    isChange = false;
}

void MacroEditor::Open()
{
    if (isChange) {
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
    isChange = false;
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
        isChange = false;
    }
}

void MacroEditor::SaveAs()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save macro", "", "NTR Files (*.ntr)");
    if (filePath.isEmpty()) return;

    currentFilePath = filePath;
    Save();
}

void MacroEditor::checkAnyChange(QListWidgetItem *item)
{
    Q_UNUSED(item);
    isChange = true;
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
    QList<QListWidgetItem*> selectedItems = ui->listMacro->selectedItems(); // Lấy danh sách các item đã chọn
    if (!selectedItems.isEmpty()) {
        QClipboard *clipboard = QGuiApplication::clipboard(); // Lấy clipboard
        QStringList textList;
        for (QListWidgetItem *item : selectedItems) {
            textList << item->text(); // Lưu nội dung vào danh sách
        }
        clipboard->setText(textList.join("\n")); // Sao chép nội dung vào clipboard
        for (QListWidgetItem *item : selectedItems) {
            delete item; // Xóa từng item đã chọn khỏi listMacro
        }
        isChange = true; // Đặt isChange thành true vì đã có thay đổi
    }
}


void MacroEditor::on_actionCopy_triggered()
{
    QList<QListWidgetItem*> selectedItems = ui->listMacro->selectedItems(); // Lấy danh sách các item đã chọn
    if (!selectedItems.isEmpty()) {
        QClipboard *clipboard = QGuiApplication::clipboard(); // Lấy clipboard
        QStringList textList;
        for (QListWidgetItem *item : selectedItems) {
            textList << item->text(); // Lưu nội dung vào danh sách
        }
        clipboard->setText(textList.join("\n")); // Sao chép nội dung vào clipboard
    }
}


void MacroEditor::on_actionPaste_triggered()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    QString text = clipboard->text();
    if (!text.isEmpty()) {
        ui->listMacro->addItem(text);
        isChange = true;
    }
}


void MacroEditor::on_actionDelete_triggered()
{
    QList<QListWidgetItem*> selectedItems = ui->listMacro->selectedItems(); // Lấy danh sách các item đã chọn
    if (!selectedItems.isEmpty()) {
        for (QListWidgetItem *item : selectedItems) {
            delete item; // Xóa từng item đã chọn khỏi listMacro
        }
        isChange = true; // Đặt isChange thành true vì đã có thay đổi
    }
}


void MacroEditor::on_actionMove_up_triggered()
{
    QList<QListWidgetItem*> selectedItems = ui->listMacro->selectedItems(); // Lấy danh sách các item đã chọn
    for (QListWidgetItem *item : selectedItems) {
        int currentRow = ui->listMacro->row(item); // Lấy chỉ số hàng của item
        if (currentRow > 0) {
            ui->listMacro->takeItem(currentRow); // Lấy item hiện tại
            ui->listMacro->insertItem(currentRow - 1, item); // Chèn item lên trên
        }
    }
    isChange = true; // Đặt isChange thành true vì đã có thay đổi
}


void MacroEditor::on_actionMove_down_triggered()
{
    QList<QListWidgetItem*> selectedItems = ui->listMacro->selectedItems(); // Lấy danh sách các item đã chọn
    for (int i = selectedItems.size() - 1; i >= 0; --i) { // Lặp ngược để tránh thay đổi chỉ số hàng
        QListWidgetItem *item = selectedItems[i];
        int currentRow = ui->listMacro->row(item); // Lấy chỉ số hàng của item
        if (currentRow < ui->listMacro->count() - 1) {
            ui->listMacro->takeItem(currentRow); // Lấy item hiện tại
            ui->listMacro->insertItem(currentRow + 1, item); // Chèn item xuống dưới
        }
    }
    isChange = true; // Đặt isChange thành true vì đã có thay đổi
}


void MacroEditor::on_actionHow_to_use_triggered()
{

}


void MacroEditor::on_listMacro_itemDoubleClicked(QListWidgetItem *item)
{
    qDebug() << item->text();
}


void MacroEditor::on_btnClick_clicked()
{
    QString txt = "click";
    ui->listMacro->addItem(txt);
    isChange = true;
}


void MacroEditor::on_btnKeyboard_clicked()
{
    QString txt = "keyboard";
    ui->listMacro->addItem(txt);
    isChange = true;
}


void MacroEditor::on_btnDelay_clicked()
{

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

