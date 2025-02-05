#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QKeyEvent>
#include "configmanager.h"
#include "mainwindow.h"

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    static SettingsWindow* getInstance();
    ~SettingsWindow();
    bool getReset();
    void setSaveToFalse();

protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_btnResetDefault_clicked();

    void on_btnSave_clicked();

    void on_sliderOpacity_sliderMoved(int position);

private:
    Ui::SettingsWindow *ui;
    explicit SettingsWindow(QWidget *parent = nullptr);
    static SettingsWindow* uniqueInstance;
    ConfigManager* configManager;
    bool isReset = false;
    bool isSave = false;
    void initWidget();
    void setMainWindowOpacity(double opac);
};

#endif // SETTINGSWINDOW_H
