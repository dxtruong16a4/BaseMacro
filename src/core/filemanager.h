#ifndef FILEMANAGER_H
#define FILEMANAGER_H

// Never used
#include <QFile>
#include <QMessageBox>
#include <QString>
#include <QTextStream>

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
