#ifndef DEFAULTCONSTANTS_H
#define DEFAULTCONSTANTS_H

#include <QAbstractButton>
#include <QApplication>
#include <QClipboard>
#include <QCloseEvent>
#include <QCursor>
#include <QDebug>
#include <QDesktopServices>
#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QKeyEvent>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QMap>
#include <QMessageBox>
#include <QSettings>
#include <QString>
#include <QStringLiteral>
#include <QPoint>
#include <QTimer>
#include <QUrl>

// #include <QWidget>

#include <unordered_map>
// #include <windows.h> /*do not include window.h lib here*/

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
const QString MYGITHUBURL = "https://github.com/dxtruong16a4/BaseMacro";
const QString ABOUT = "Base Macro - Developed by\ndxtruong16a4 & nhanvatphu04\nVersion: 1.0.1";

const QString DWINDOW = QStringLiteral(
                            "[Window]\nWidth=%1\nHeight=%2\nX=%3\nY=%4\n\n"
                        ).arg(DWIDTH).arg(DHEIGHT).arg(DPOSX).arg(DPOSY);

const QString DSETTINGS = QStringLiteral(
                            "[Settings]\nPin=%1\nOpa=%2\nHide=%3\n"
                        ).arg(DPIN).arg(DOPACITY).arg(DHIDE ? "true" : "false");

const QString CONFIGSAMPLE = DWINDOW + DSETTINGS;
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

// Mouse action
enum MouseMode {
    LEFT,
    RIGHT,
    WHEEL,
    HORIZONTALWHEEL,
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

// Clipboard action
enum ClipboardMode {
    CLEARCLIPBOARD,
    SETCLIPBOARD,
    PASTETEXT
};

// Open action
enum OpenMode {
    OPENFILE,
    OPENPROGRAM,
    OPENWEBSITE
};

// Window action
enum WindowMode {
    SWITCHWINDOW,
    CLOSEWINDOW,
    MOVEWINDOW,
    RESIZEWINDOW,
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

// Switch Action
enum SwitchMode {
    SWITCH,
    CASE,
    CASEDEFAULT,
    ENDSWITCH
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
std::string modeToString(T mode) {
    static std::unordered_map<int, std::string> enumMap = {
        // MOUSE
        {LEFT           , "LEFT"},
        {RIGHT          , "RIGHT"},
        {WHEEL          , "WHEEL"},
        {HORIZONTALWHEEL, "HORIZONTALWHEEL"},
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
        //CLIPBOARD
        {CLEARCLIPBOARD , "CLEARCLIPBOARD"},
        {SETCLIPBOARD   , "SETCLIPBOARD"},
        {PASTETEXT      , "PASTETEXT"},
        // OPEN
        {OPENFILE       , "OPENFILE"},
        {OPENPROGRAM    , "OPENPROGRAM"},
        {OPENWEBSITE    , "OPENWEBSITE"},
        // WINDOW
        {SWITCHWINDOW   , "SWITCHWINDOW"},
        {CLOSEWINDOW    , "CLOSEWINDOW"},
        {MOVEWINDOW     , "MOVEWINDOW"},
        {RESIZEWINDOW   , "RESIZEWINDOW"},
        // IF
        {IFIMAGEFOUND   , "IFIMAGEFOUND"},
        {IFWINDOWEXIST  , "IFWINDOWEXIST"},
        {IFWINDOWFOCUS  , "IFWINDOWFOCUS"},
        {IFITERATOREQUAL, "IFITERATOREQUAL"},
        {ELSEIF         , "ELSEIF"},
        {ENDIF          , "ENDIF"},
        // SWITCH
        {SWITCH         , "SWITCH"},
        {CASE           , "CASE"},
        {CASEDEFAULT    , "CASEDEFAULT"},
        {ENDSWITCH      , "ENDSWITCH"},
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

#endif // DEFAULTCONSTANTS_H
