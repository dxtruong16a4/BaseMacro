#ifndef DIALOGKEYBOARD_H
#define DIALOGKEYBOARD_H

#include "../core/DialogBase.h"
#include "../widgets/macroeditor.h"

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
    void keyPressEvent(QKeyEvent *event) override;

    // Method for dragging the icon to get the window title
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void eventTypeChange();

    void on_chbFocusWindow_clicked(bool checked);

    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::DialogKeyboard *ui;
    QMap<int, QString> keyMap;
    bool isEditing = false;
    QListWidgetItem *editingItem = nullptr;

    // Attribute for dragging the icon to get the window title
    bool tracking = false;
    QLabel *lbGetWindowTitle;
    QTimer *trackingTimer;

    // Method for dragging the icon to get the window title
    void startTracking();
    void updateWindowTitle();
    void stopTracking();

    void resetToDefault();

    void disableCombinationWidget();
    void enableCombinationWidget();

    void disableRepeatWidget();
    void enableRepeatWidget();

    void disableFocusWidget();
    void enableFocusWidget();

    QString getData();

};

#endif // DIALOGKEYBOARD_H
