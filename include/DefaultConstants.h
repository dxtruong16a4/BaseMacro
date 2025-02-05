#ifndef DEFAULTCONSTANTS_H
#define DEFAULTCONSTANTS_H

#include <QString>
#include <QStringLiteral>
#include <QMap>
#include <QPoint>

// Value
constexpr int DWIDTH = 800;
constexpr int DHEIGHT = 600;
constexpr int DPOSX = 960 - DWIDTH / 2;
constexpr int DPOSY = 540 - DHEIGHT / 2;
constexpr int MW = 300;
constexpr int MH = 200;
const QString DPIN = "Topleft";
constexpr int DOPACITY = 100;
constexpr bool DHIDE = true;

// Text
const QString MYGITHUBURL = "https://github.com/nhanvatphu04";

const QString CWINDOW = QStringLiteral(
                            "[Window]\nWidth=%1\nHeight=%2\nX=%3\nY=%4\n\n"
                        ).arg(DWIDTH).arg(DHEIGHT).arg(DPOSX).arg(DPOSY);

const QString DSETTINGS = QStringLiteral(
                            "[Settings]\nPin=%1\nOpa=%2\nHide=%3\n"
                        ).arg(DPIN).arg(DOPACITY).arg(DHIDE ? "true" : "false");

const QString CONFIGSAMPLE = CWINDOW + DSETTINGS;
const QString FILEPATH = QStringLiteral("config.ini");

// Corner
const QMap<QString, QPoint> DCORNER = {
    {"Topleft", QPoint(0, 0)},
    {"Topright", QPoint(1920 - MW, 0)},
    {"Bottomleft", QPoint(0, 1080 - MH - 30)},
    {"Bottomright", QPoint(1920 - MW, 1080 - MH - 30)}
};

#endif // DEFAULTCONSTANTS_H
