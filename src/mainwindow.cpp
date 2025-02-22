#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow* MainWindow::uniqueInstance = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    configManager = new ConfigManager(SETTINGFILEPATH);
    this->setGeometry(
        configManager->getX(),
        configManager->getY() + 31,
        configManager->getWidth(),
        configManager->getHeight()
    );
    this->setWindowOpacity(configManager->getOpacity() / 100.0);
}

MainWindow* MainWindow::getInstance()
{
    if (uniqueInstance == nullptr) {
        uniqueInstance = new MainWindow();
    }
    return uniqueInstance;
}

MainWindow::~MainWindow()
{
    delete configManager;
    if (uniqueInstance == this) {
        uniqueInstance = nullptr;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (isPinned) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Base Macro");
        msgBox.setText("Unpin to exit!");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();

        event->ignore();
        this->show();
    }
    else {
        saveConfig();
        event->accept();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F1) {
        MacroEditor *me = MacroEditor::getInstance();
        if (me){
            me->show();
        }
    }
}

void MainWindow::moveEvent(QMoveEvent *event)
{
    if (!isPinned) {
        PosBeforePinned = this->pos();
    }
    else {
        this->move(getCorner(configManager->getPinCorner()).x(), getCorner(configManager->getPinCorner()).y());
    }
}

void MainWindow::showEvent(QShowEvent *event){
    QMainWindow::showEvent(event);
    if (isPinned) {
        this->activateWindow();
        this->raise();
    }
}

void MainWindow::on_actionNew_triggered()
{

}

void MainWindow::on_actionOpen_triggered()
{

}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionSave_As_triggered()
{

}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCut_triggered()
{

}

void MainWindow::on_actionCopy_triggered()
{

}

void MainWindow::on_actionPaste_triggered()
{

}

void MainWindow::on_actionDelete_triggered()
{

}

void MainWindow::on_actionMove_up_triggered()
{

}

void MainWindow::on_actionMove_down_triggered()
{

}

void MainWindow::on_actionSettings_triggered()
{
    SettingsWindow *sw = SettingsWindow::getInstance();
    if (sw){
        sw->setSave(false);
        sw->move(getCenteredPosition(this, sw));
        sw->show();
    }
}

void MainWindow::on_actionPin_window_triggered()
{
    MainWindow::pinWindow(!isPinned);
}

void MainWindow::on_actionHow_to_use_triggered()
{
    DialogHowToUse *dh = DialogHowToUse::getInstance();
    if (dh){
        dh->move(getCenteredPosition(this, dh));
        dh->show();
    }
}

void MainWindow::on_actionTips_triggered()
{
    DialogTips *dt = DialogTips::getInstance();
    if (dt){
        dt->move(getCenteredPosition(this, dt));
        dt->show();
    }
}

void MainWindow::on_actionAbout_triggered()
{
    DialogAbout *da = DialogAbout::getInstance();
    if (da){
        da->move(getCenteredPosition(this, da));
        da->show();
    }
}

void MainWindow::on_btnRun_clicked()
{
    // QString otherapp = QDir::currentPath() + "/untitled.exe";
    // QProcess::startDetached(otherapp);
}

void MainWindow::on_btnStop_clicked()
{

}

void MainWindow::on_btnOpenEditor_clicked()
{
    MacroEditor *me = MacroEditor::getInstance();
    if (me){
        me->move(getCenteredPosition(this, me));
        me->show();
    }
}

QPoint MainWindow::getCorner(const QString &key)
{
    return DCORNER.value(key, QPoint(0, 0));
}

QPoint MainWindow::getCenteredPosition(QWidget *parent, QWidget *child)
{
    if (!parent || !child)
        return QPoint(0, 0);
    QRect parentRect = parent->geometry();
    QRect childRect = child->geometry();
    int x = parentRect.x() + (parentRect.width() - childRect.width()) / 2;
    int y = parentRect.y() + (parentRect.height() - childRect.height()) / 2;
    return QPoint(x, y);
}

void MainWindow::pinWindow(bool pinned)
{
    if (pinned) {
        isPinned = true;
        PosBeforePinned = this->pos();
        SizeBeforePinned = QPoint(this->width(), this->height());
        this->setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
        this->setGeometry(
            getCorner(configManager->getPinCorner()).x(),
            getCorner(configManager->getPinCorner()).y(),
            this->minimumSize().width(),
            this->minimumSize().height()
            );
    } else {
        isPinned = false;
        this->setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
        this->setGeometry(
            PosBeforePinned.x(),
            PosBeforePinned.y() + 31,
            SizeBeforePinned.x(),
            SizeBeforePinned.y()
            );
    }
    this->show();
}

void MainWindow::saveConfig()
{
    configManager->setWidth(this->width());
    configManager->setHeight(this->height());
    configManager->setX(this->x());
    configManager->setY(this->y());
}
