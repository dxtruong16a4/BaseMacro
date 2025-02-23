#ifndef DIALOGDELAY_H
#define DIALOGDELAY_H

#include "../core/DialogBase.h"
#include "../widgets/macroeditor.h"

namespace Ui {
class DialogDelay;
}

class DialogDelay : public DialogBase
{
    Q_OBJECT

public:
    explicit DialogDelay(QWidget *parent = nullptr);
    ~DialogDelay();
    void editItem(QListWidgetItem *item);
    void setData(const QString& data) override;

protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_tabWidget_currentChanged(int index);

    // Delay time
    void on_sbTotal_valueChanged(int arg1);

    void on_sbMinutes_valueChanged(int arg1);

    void on_sbSeconds_valueChanged(int arg1);

    void on_sbMilliseconds_valueChanged(int arg1);
    // Delay window
    // Delay user input
    // button handle
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::DialogDelay *ui;
    bool isEditing = false;
    QListWidgetItem *editingItem = nullptr;

    void resetToDefault();

    QString getData();
};

#endif // DIALOGDELAY_H
