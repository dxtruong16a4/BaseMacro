#include "helper.h"

/**
 * @brief Get the title of the window at the current cursor position.
 *
 * This function uses the Win32 API to identify the window under the mouse cursor
 * and then retrieves the title of the root owner window.
 *
 * @return QString - The window title, or "NOTFOUND" if no window is found.
 */
QString getWindowTitle() {
    QPoint pos = QCursor::pos();
    HWND hwnd = WindowFromPoint(POINT{pos.x(), pos.y()});

    if (hwnd) {
        hwnd = GetAncestor(hwnd, GA_ROOTOWNER);
        char windowTitle[256];
        GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));
        return QString::fromLocal8Bit(strlen(windowTitle) > 0 ? windowTitle : "NONAME");
    }

    return "NOTFOUND";
}

/**
 * @brief Start a drag operation with a QLabel containing an icon.
 *
 * Creates a QDrag object using the specified QLabel, allowing the icon
 * to be dragged without performing a drop action (IgnoreAction).
 *
 * @param parent The parent widget used for QDrag.
 * @param iconLabel The QLabel containing the icon to be dragged.
 */
void startTrackingDrag(QWidget *parent, QLabel *iconLabel)
{
    if (!iconLabel || !iconLabel->isVisible()) return;

    QMimeData *mimeData = new QMimeData();
    QDrag *drag = new QDrag(parent);
    drag->setMimeData(mimeData);
    drag->setPixmap(iconLabel->pixmap(Qt::ReturnByValue));

    drag->exec(Qt::IgnoreAction);
}



void compileMacro(QWidget *parent, const QString& sourceFile, const QString& outputFile){
    QString compilerPath = QCoreApplication::applicationDirPath() + "/mingw/bin/g++.exe";
    QProcess process;
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("PATH", QCoreApplication::applicationDirPath() + "/mingw/bin");
    process.setProcessEnvironment(env);

    process.setProgram(compilerPath);
    process.setArguments({sourceFile, "-o", outputFile});
    process.setWorkingDirectory(QCoreApplication::applicationDirPath());
    process.start();
    process.waitForFinished();

    if (process.exitCode() != 0) {
        QMessageBox::warning(parent, "Error", "Compilation failed: " + process.readAllStandardError());
    } else {
        QMessageBox::information(parent, "Success", "Executable created: " + outputFile);
    }
}

void analyseAction(QStringList parts) {
    if (parts[0] == "MOUSE") {
        // Handle mouse action
    } else if (parts[0] == "KEYBOARD") {
        // Handle keyboard action
    } else if (parts[0] == "DELAY") {
        // Handle delay action
    } else {
        // Handle other actions
    }
}

void buildMouseAction(QStringList parts) {
    // MOUSE <EVENTTYPEINDEX> <TIMES> <MS> <X> <Y> <WHEEL> <WINDOWTITLE>
    if (parts.size() < 8) return;
    int eventTypeIndex = parts[1].toInt();
    int times = parts[2].toInt();
    int ms = parts[3].toInt();
    int x = parts[4].toInt();
    int y = parts[5].toInt();
    int wheel = parts[6].toInt();
    QString windowTitle = parts[7];
    // Build the mouse action here
    QString generatedCode = "";
    if (eventTypeIndex == 0) {
        // Left click
    } else if (eventTypeIndex == 1) {
        // Right click
    } else if (eventTypeIndex == 2) {
        // Middle click
    }
}