#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QString>
#include <QVector>
#include <QDebug>

#include "DefaultConstants.h"
#include "ConfigManager.h"
#include "settingswindow.h"
#include "dialoghowtouse.h"
#include "dialogabout.h"
#include "dialogtips.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ~MainWindow();
    static MainWindow* getInstance();

private slots:

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

    void on_actionSettings_triggered();

    void on_actionPin_window_triggered();

    void on_actionHow_to_use_triggered();

    void on_actionTips_triggered();

    void on_actionAbout_triggered();

private:
    MainWindow(QWidget *parent = nullptr);
    Ui::MainWindow *ui;
    static MainWindow* uniqueInstance;

    bool isPinned = false;
    QPoint PosBeforePinned = QPoint(DPOSX, DPOSY);
    QPoint SizeBeforePinned = QPoint(DWIDTH, DHEIGHT);
    QPoint getCorner(const QString& key);
    ConfigManager *configManager;
    void cleanUp();
    void SaveConfig();
    void PinWindow(bool pinned);

protected:
    void closeEvent(QCloseEvent *event) override;
    void moveEvent(QMoveEvent *event) override;
    void showEvent(QShowEvent *event) override;
};
#endif // MAINWINDOW_H
