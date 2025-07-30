#include "filemanager.h"

FileManager::FileManager(const QString& path) : filePath(path), file(path) {
    if (filePath.isEmpty()) {
        throw std::invalid_argument("File path is empty!");
    }
}

FileManager::~FileManager() {
    if (file.isOpen()) {
        file.close();
    }
}

void FileManager::write(const QString& data) {
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        throw std::runtime_error("Cannot open file " + filePath.toStdString() + " to write!");
    }
    QTextStream out(&file);
    out << data << "\n";
    file.close();
}

QString FileManager::read() {
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error("Cannot open file " + filePath.toStdString() + " to read!");
    }
    QTextStream in(&file);
    QString content = in.readAll();
    file.close();
    return content;
}

QString FileManager::createFile(const QString &directory)
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
    QString fileName = directory + "/" + timestamp + ".txt";
    QFile newFile(fileName);
    if (!newFile.open(QIODevice::WriteOnly)) {
        throw std::runtime_error("Cannot create file " + fileName.toStdString());
    }
    newFile.close();
    return fileName;
}

void FileManager::deleteFile(const QString &path)
{
    QFile fileToDelete(path);
    if (!fileToDelete.exists()) {
        throw std::runtime_error("File " + path.toStdString() + " does not exist!");
    }
    if (!fileToDelete.remove()) {
        throw std::runtime_error("Failed to delete file " + path.toStdString());
    }
}
