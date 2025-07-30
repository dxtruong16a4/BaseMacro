#include "macrobuild.h"
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

std::unique_ptr<MacroBuild> MacroBuild::uniqueInstance = nullptr;

MacroBuild* MacroBuild::getInstance() {
    if (!uniqueInstance) {
        uniqueInstance = std::make_unique<MacroBuild>();
    }
    return uniqueInstance.get();
}

MacroBuild::MacroBuild() {
    fm = new FileManager(filename);

}

MacroBuild::~MacroBuild() {
    delete fm;
}

// MOUSE EVENTTYPEINDEX TIMES MS X Y FLAG 0
void MacroBuild::insertAction(const QString action) {
    QStringList parts = this->getContent(action);
}

QString MacroBuild::getActionType(const QString &data){
    QRegularExpression regex(R"(^(\s*)(\S.*)$)");
    QRegularExpressionMatch match = regex.match(data);
    if (!match.hasMatch()) return QString();
    QString content = match.captured(1);
    return content;
}

QStringList MacroBuild::getContent(const QString& data) {
    QRegularExpression regex(R"(^(\s*)(\S.*)$)");
    QRegularExpressionMatch match = regex.match(data);
    if (!match.hasMatch()) return QStringList();
    QString content = match.captured(2);
    return content.split(" ", Qt::SkipEmptyParts);
}
