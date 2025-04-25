#ifndef HELPER_H
#define HELPER_H

#include <QCoreApplication>
#include <QCursor>
#include <QLabel>
#include <QDrag>
#include <QMessageBox>
#include <QMimeData>
#include <QWidget>
#include <QString>
#include <QPoint>
#include <QProcess>

#include <Windows.h>

QString getWindowTitle();
void startTrackingDrag(QWidget *parent, QLabel *iconLabel);
void CompileMacro(QWidget *parent, const QString& sourceFile, const QString& outputFile);

#endif
