#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./core/DefaultConstants.h"
#include "./core/ConfigManager.h"
#include "./widgets/settingswindow.h"
#include "./widgets/dialoghowtouse.h"
#include "./widgets/dialogabout.h"
#include "./widgets/dialogtips.h"
#include "./widgets/macroeditor.h"

#include <QMainWindow>
#include <QEvent>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QString>
#include <QVector>
#include <QProcess>
#include <QDebug>

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

protected:
    void closeEvent(QCloseEvent *event) override;
    void moveEvent(QMoveEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

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

    void on_btnRun_clicked();

    void on_btnOpenEditor_clicked();

    void on_btnStop_clicked();

private:
    MainWindow(QWidget *parent = nullptr);
    Ui::MainWindow *ui;
    static MainWindow* uniqueInstance;

    bool isPinned = false;
    QPoint PosBeforePinned = QPoint(DPOSX, DPOSY);
    QPoint SizeBeforePinned = QPoint(DWIDTH, DHEIGHT);
    QPoint getCorner(const QString& key);
    ConfigManager *configManager;
    void SaveConfig();
    void PinWindow(bool pinned);
    QPoint getCenteredPosition(QWidget *parent, QWidget *child);
};

#endif // MAINWINDOW_H
