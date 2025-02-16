#ifndef DEFAULTCONSTANTS_H
#define DEFAULTCONSTANTS_H

#include <QString>
#include <QStringLiteral>
#include <QMap>
#include <QPoint>
#include <iostream>
#include <unordered_map>

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
const QString SETTINGFILEPATH = QStringLiteral("config.ini");
const QString APPDIRPATH = "";

// Corner
const QMap<QString, QPoint> DCORNER = {
    {"Topleft", QPoint(0, 0)},
    {"Topright", QPoint(1920 - MW, 0)},
    {"Bottomleft", QPoint(0, 1080 - MH - 30)},
    {"Bottomright", QPoint(1920 - MW, 1080 - MH - 30)}
};

// Action type

// Click action
enum ClickMode {
    LEFT,
    RIGHT,
    WHEELUP,
    WHEELDOWN,
    MOVE,
};

// Keyboard action
enum KeyboardMode {
    KEYPRESS,
    KEYUP,
    KEYDOWN,
    KEYCOMBINATION
};

// Delay action
enum DelayMode {
    DELAYTIME,
    DELAYWINDOW,
    DELAYUSERINPUT
};

// Paste action
enum PasteMode {
    PASTETEXT
};

// Open website action
enum OpenWebsiteMode {
    OPENWEBSITE
};

// If action
enum IfMode {
    IFIMAGEFOUND,
    IFWINDOWEXIST,
    IFWINDOWFOCUS,
    IFITERATOREQUAL,
    ELSEIF,
    ENDIF
};

// Loop action
enum LoopMode {
    FOR,
    WHILE,
    BREAK,
    CONTINUE,
    EXITLOOP
};

// Bracket action
enum BracketMode {
    OPENBRACE,
    CLOSEBRACE
};

// Label action
enum LabelMode {
    LABEL
};

// Goto action
enum GotoMode {
    GOTO
};

// Stop action
enum StopMode {
    STOP
};

// Run code action
enum RunCodeMode {
    RUNCODE
};

// Mode to string

template <typename T>
std::string ModeToString(T mode) {
    static std::unordered_map<int, std::string> enumMap = {
        // MOUSE
        {LEFT           , "LEFT"},
        {RIGHT          , "RIGHT"},
        {WHEELUP        , "WHEELUP"},
        {WHEELDOWN      , "WHEELDOWN"},
        {MOVE           , "MOVE"},
        // KEYBOARD
        {KEYPRESS       , "KEYPRESS"},
        {KEYUP          , "KEYUP"},
        {KEYDOWN        , "KEYDOWN"},
        {KEYCOMBINATION , "KEYCOMBINATION"},
        //DELAY
        {DELAYTIME      , "DELAYTIME"},
        {DELAYWINDOW    , "DELAYWINDOW"},
        {DELAYUSERINPUT , "DELAYUSERINPUT"},
        //PASTE
        {PASTETEXT      , "PASTETEXT"},
        // OPENWEBSITE
        {OPENWEBSITE    , "OPENWEBSITE"},
        // IF
        {IFIMAGEFOUND   , "IFIMAGEFOUND"},
        {IFWINDOWEXIST  , "IFWINDOWEXIST"},
        {IFWINDOWFOCUS  , "IFWINDOWFOCUS"},
        {IFITERATOREQUAL, "IFITERATOREQUAL"},
        {ELSEIF         , "ELSEIF"},
        {ENDIF          , "ENDIF"},
        // LOOP
        {FOR            , "FOR"},
        {WHILE          , "WHILE"},
        {BREAK          , "BREAK"},
        {CONTINUE       , "CONTINUE"},
        {EXITLOOP       , "EXITLOOP"},
        // BRACE
        {OPENBRACE      , "OPENBRACE"},
        {CLOSEBRACE     , "CLOSEBRACE"},
        // LABEL
        {LABEL          , "LABEL"},
        // GOTO
        {GOTO           , "GOTO"},
        // STOP
        {STOP           , "STOP"},
        // CODE
        {RUNCODE        , "RUNCODE"},
    };

    auto it = enumMap.find(static_cast<int>(mode));
    return (it != enumMap.end()) ? it->second : "UNKNOWN";
}

/*
Định nghĩa cho action
MOUSE: CLICK
KEYBOARD
DELAY

*/

#endif // DEFAULTCONSTANTS_H
