#include "mainwindow.h"

#include <QApplication>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    QSharedMemory sharedMemory("MyUniqueAppIdentifier");
    if (!sharedMemory.create(1)) {
        return 0;
    }
    QApplication a(argc, argv);
    MainWindow *w = MainWindow::getInstance();
    w->show();
    return a.exec();
}
