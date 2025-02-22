#ifndef DIALOGKEYBOARD_H
#define DIALOGKEYBOARD_H

#include "../core/DialogBase.h"
#include "../widgets/macroeditor.h"

#include <QDialog>
#include <QCloseEvent>
#include <QListWidgetItem>
#include <QMap>
#include <QMessageBox>
#include <QString>

namespace Ui {
class DialogKeyboard;
}

class DialogKeyboard : public DialogBase
{
    Q_OBJECT

public:
    explicit DialogKeyboard(QWidget *parent = nullptr);
    ~DialogKeyboard();
    void editItem(QListWidgetItem *item);
    void setData(const QString& data) override;    

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void eventTypeChange();

    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::DialogKeyboard *ui;
    QMap<int, QString> keyMap;
    bool isEditing = false;
    QListWidgetItem *editingItem = nullptr;

    void resetToDefault();

    void disableCombinationWidget();
    void enableCombinationWidget();

    void disableRepeatWidget();
    void enableRepeatWidget();

    QString getData();
};

#endif // DIALOGKEYBOARD_H
