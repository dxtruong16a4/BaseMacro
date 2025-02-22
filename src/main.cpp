#include "mainwindow.h"

#include "core/dialogpool.h"

#include <QApplication>
#include <QSharedMemory>
#include <QObject>

int main(int argc, char *argv[])
{
    QSharedMemory sharedMemory("MyUniqueAppIdentifier");
    if (!sharedMemory.create(1)) {
        return 0;
    }
    QApplication a(argc, argv);
    MainWindow *w = MainWindow::getInstance();
    w->show();
    // QObject::connect(&a, &QApplication::aboutToQuit, []() {
    //     DialogPool::instance().releaseAllDialogs();
    // });
    return a.exec();
}
