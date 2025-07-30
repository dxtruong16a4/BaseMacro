#include "mainwindow.h"

// #include "core/dialogpool.h"

#include <QApplication>
#include <QSharedMemory>
#include <QFile>
#include <QTextStream>
#include <QDir>
// #include <QObject>

int main(int argc, char *argv[])
{
    QSharedMemory sharedMemory("MyUniqueAppIdentifier");
    if (!sharedMemory.create(1)) {
        return 0;
    }
    QApplication a(argc, argv);
    
    // Load and apply stylesheet
    QFile styleFile(":/resources/style.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream styleStream(&styleFile);
        QString styleSheet = styleStream.readAll();
        a.setStyleSheet(styleSheet);
        styleFile.close();
        qDebug() << "Stylesheet loaded successfully from resources/style.qss";
    } else {
        qDebug() << "Could not open resources/style.qss file";
        qDebug() << "Error:" << styleFile.errorString();
        qDebug() << "Trying alternative path...";
        
        // Try alternative path (legacy)
        QFile altStyleFile(":/style.qss");
        if (altStyleFile.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream altStyleStream(&altStyleFile);
            QString altStyleSheet = altStyleStream.readAll();
            a.setStyleSheet(altStyleSheet);
            altStyleFile.close();
            qDebug() << "Stylesheet loaded from alternative path (legacy)";
        } else {
            qDebug() << "Could not open alternative path either";
            qDebug() << "No stylesheet will be applied";
        }
    }
    
    MainWindow *w = MainWindow::getInstance();
    w->show();
    // QObject::connect(&a, &QApplication::aboutToQuit, []() {
    //     DialogPool::instance().releaseAllDialogs();
    // });
    return a.exec();
}
