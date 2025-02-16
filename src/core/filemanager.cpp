// Not used

#include "filemanager.h"

FileManager::FileManager(const QString& path) : filePath(path), file(path) {}

FileManager::~FileManager() {
    if (file.isOpen()) {
        file.close();
    }
}

void FileManager::write(const QString& data) {
    if (filePath.isEmpty()) {
        QMessageBox::warning(nullptr, "Error", "File path is empty!");
        return;
    }
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        QMessageBox::warning(nullptr, "Error", "Cannot open file " + filePath + " to write!");
        return;
    }
    QTextStream out(&file);
    out << data << "\n";
    file.close();
}

QString FileManager::read() const {
    if (filePath.isEmpty()) {
        QMessageBox::warning(nullptr, "Error", "File path is empty!");
        return "";
    }
    QFile readFile(filePath);
    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "Cannot open file " + filePath + " to read!");
        return "";
    }
    QTextStream in(&readFile);
    QString content = in.readAll();
    readFile.close();
    return content;
}
