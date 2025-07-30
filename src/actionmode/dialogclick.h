#ifndef DIALOGCLICK_H
#define DIALOGCLICK_H

#include "../core/DialogBase.h"
// #include "../widgets/macroeditor.h"
/**
 * the line include mainwindow below has already included macroeditor.
 * if we separate main window and macroeditor window, you can include it.
 */
#include "../mainwindow.h"

namespace Ui {
class DialogClick;
}

class DialogClick : public DialogBase
{
    Q_OBJECT

public:
    explicit DialogClick(QWidget *parent = nullptr);
    ~DialogClick();
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

    void getMousePos();

    void on_chbFocusWindow_clicked(bool checked);

    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::DialogClick *ui;
    QTimer *timer;
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

    void disableWheelWidget();
    void enableWheelWidget();

    void disableRepeatWidget();
    void enableRepeatWidget();

    void disableFocusWidget();
    void enableFocusWidget();

    void showOtherWindow();
    void hideOtherWindow();

    QString getData();

};

#endif // DIALOGCLICK_H
