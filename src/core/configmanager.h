#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "DefaultConstants.h"

class ConfigManager
{
public:
    ConfigManager(const QString& filePath);
    ~ConfigManager();
    bool configFileExists() const;
    bool ensureDefaultConfigCreated();
    void loadSettings(int& width, int& height, int& x, int& y, QString& pinCorner, int& opac, bool& isHide);
    void saveSettings(int width, int height, int x, int y, const QString& pinCorner, int opac, bool isHide);
    // Setter
    void setWidth(int width);
    void setHeight(int height);
    void setX(int x);
    void setY(int y);
    void setPinCorner(QString pinCorner);
    void setOpacity(int opac);
    void setHide(bool isHide);
    // Getter
    int getWidth();
    int getHeight();
    int getX();
    int getY();
    QString getPinCorner();
    int getOpacity();
    bool getHide();

private:
    QString configFilePath = SETTINGFILEPATH;
    const QString configSample = CONFIGSAMPLE;
    QSettings settings;
};

#endif // CONFIGMANAGER_H
