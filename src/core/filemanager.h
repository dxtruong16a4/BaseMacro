#ifndef FILEMANAGER_H
#define FILEMANAGER_H

// Not used

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QMessageBox>

class FileManager
{
public:
    explicit FileManager(const QString& path);
    ~FileManager();
    void write(const QString& data);
    QString read() const;

private:
    QString filePath;
    QFile file;
};

#endif // FILEMANAGER_H
