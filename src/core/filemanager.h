#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QDateTime>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <stdexcept>

class FileManager
{
public:
    explicit FileManager(const QString& path);
    ~FileManager();
    void write(const QString& data);
    QString read();
    static QString createFile(const QString& directory);
    static void deleteFile(const QString& path);

private:
    QString filePath;
    QFile file;
};

#endif // FILEMANAGER_H
