#ifndef MACROBUILD_H
#define MACROBUILD_H

#include <memory>
#include <QStringList>
#include <QRegularExpression>
#include "filemanager.h"

class MacroBuild
{
public:
    static MacroBuild* getInstance();
    ~MacroBuild();

private:
    MacroBuild();
    static std::unique_ptr<MacroBuild> uniqueInstance;
    friend std::unique_ptr<MacroBuild> std::make_unique<MacroBuild>();
    FileManager *fm;
    QString filename;

    void insertAction(const QString action);
    QString getActionType(const QString&data);
    QStringList getContent(const QString& data);
};

#endif // MACROBUILD_H
