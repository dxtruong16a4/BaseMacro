#ifndef MACROEDITOR_H
#define MACROEDITOR_H

#include "../core/filemanager.h"

#include <memory>
#include <QMainWindow>
#include <QCloseEvent>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QClipboard>

namespace Ui {
class MacroEditor;
}

class MacroEditor : public QMainWindow
{
    Q_OBJECT

public:
    static MacroEditor* getInstance();
    ~MacroEditor();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    // QT generator
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionExit_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionDelete_triggered();

    void on_actionMove_up_triggered();

    void on_actionMove_down_triggered();

    void on_actionHow_to_use_triggered();

    void on_listMacro_itemDoubleClicked(QListWidgetItem *item);

    void on_btnClick_clicked();

    // Custom
    void checkAnyChange(QListWidgetItem *item);

    void on_btnKeyboard_clicked();

    void on_btnDelay_clicked();

    void on_btnPaste_clicked();

    void on_btnOpenLink_clicked();

    void on_btnFind_clicked();

    void on_btnIf_clicked();

    void on_btnLoop_clicked();

    void on_btnBracket_clicked();

    void on_btnLabel_clicked();

    void on_btnGoto_clicked();

    void on_btnBreak_Continue_clicked();

    void on_btnStop_clicked();

    void on_btnCode_clicked();

private:
    Ui::MacroEditor *ui;
    explicit MacroEditor(QWidget *parent = nullptr);
    static std::unique_ptr<MacroEditor> uniqueInstance;
    friend std::unique_ptr<MacroEditor> std::make_unique<MacroEditor>();

    QString currentFilePath = "";
    bool isChange = false;
    void New();
    void Open();
    void Save();
    void SaveAs();
};

#endif // MACROEDITOR_H
