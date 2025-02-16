#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include "../core/configmanager.h"
#include "../mainwindow.h"

#include <memory>
#include <QWidget>
#include <QKeyEvent>

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
    static std::unique_ptr<SettingsWindow> uniqueInstance;
    friend std::unique_ptr<SettingsWindow> std::make_unique<SettingsWindow>();
    ConfigManager* configManager;
    bool isReset = false;
    bool isSave = false;
    void initWidget();
    void setMainWindowOpacity(double opac);
};

#endif // SETTINGSWINDOW_H
