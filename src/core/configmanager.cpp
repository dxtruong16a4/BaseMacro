#include "configmanager.h"

ConfigManager::ConfigManager(const QString& filePath) : configFilePath(filePath), settings(filePath, QSettings::IniFormat) {
    if (!configFileExists()) {
        if (createDefaultConfig()) {
            // qDebug() << "File config.ini created successfully.";
        }
    } else {
        // qDebug() << "File config.ini exists.";
    }
}

bool ConfigManager::configFileExists() const {
    QFileInfo fileInfo(configFilePath);
    return fileInfo.exists() && fileInfo.isFile();
}

bool ConfigManager::createDefaultConfig() {
    QFile configFile(configFilePath);
    if (!configFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, QLatin1String("Error"),
                             QLatin1String("Error creating config file: ") + configFile.errorString());
        return false;
    }
    QTextStream out(&configFile);
    out << configSample;
    return true;
}

void ConfigManager::loadSettings(int& width, int& height, int& x, int& y, QString& pinCorner, int& opac, bool& isHide)
{
    width = settings.value("Window/Width", DWIDTH).toInt();
    height = settings.value("Window/Height", DHEIGHT).toInt();
    x = settings.value("Window/X", DPOSX).toInt();
    y = settings.value("Window/Y", DPOSY).toInt();
    pinCorner = settings.value("Settings/Pin", DPIN).toString();
    opac = settings.value("Setting/Opa", DOPACITY).toInt();
    isHide = settings.value("Setting/Hide", DHIDE).toBool();
}

void ConfigManager::saveSettings(int width, int height, int x, int y, const QString& pinCorner, int opac, bool isHide)
{
    settings.setValue("Window/Width", width);
    settings.setValue("Window/Height", height);
    settings.setValue("Window/X", x);
    settings.setValue("Window/Y", y);
    settings.setValue("Settings/Pin", pinCorner);
    settings.setValue("Settings/Opa", opac);
    settings.setValue("Settings/Hide", isHide);
    settings.sync();
}

void ConfigManager::setWidth(int width)
{
    settings.setValue("Window/Width", width);
    settings.sync();
}

void ConfigManager::setHeight(int height)
{
    settings.setValue("Window/Height", height);
    settings.sync();
}

void ConfigManager::setX(int x)
{
    settings.setValue("Window/X", x);
    settings.sync();
}

void ConfigManager::setY(int y)
{
    settings.setValue("Window/Y", y);
    settings.sync();
}

void ConfigManager::setPinCorner(QString pinCorner)
{
    settings.setValue("Settings/Pin", pinCorner);
    settings.sync();
}

void ConfigManager::setOpacity(int opac)
{
    settings.setValue("Settings/Opa", opac);
    settings.sync();
}

void ConfigManager::setHide(bool isHide)
{
    settings.setValue("Settings/Hide", isHide);
    settings.sync();
}

int ConfigManager::getWidth()
{
    return settings.value("Window/Width", DWIDTH).toInt();
}

int ConfigManager::getHeight()
{
    return settings.value("Window/Height", DHEIGHT).toInt();
}

int ConfigManager::getX()
{
    return settings.value("Window/X", DPOSX).toInt();
}

int ConfigManager::getY()
{
    return settings.value("Window/Y", DPOSY).toInt();
}

QString ConfigManager::getPinCorner()
{
    return settings.value("Settings/Pin", DPIN).toString();
}

int ConfigManager::getOpacity()
{
    return settings.value("Settings/Opa", DOPACITY).toInt();
}

bool ConfigManager::getHide()
{
    return settings.value("Settings/Hide", DHIDE).toBool();
}
