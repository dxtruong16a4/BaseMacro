#ifndef DIALOGBASE_H
#define DIALOGBASE_H

#include <memory>

#include <QApplication>
#include <QCloseEvent>
#include <QDialog>
#include <QListWidgetItem>
#include <QMap>
#include <QString>

class DialogBase : public QDialog
{
    Q_OBJECT
public:
    explicit DialogBase(QWidget *parent = nullptr) : QDialog(parent) {}
    virtual ~DialogBase() {}
    virtual void editItem(QListWidgetItem *item) = 0;
    virtual void setData(const QString&) = 0;

    /**
     * @brief Extracts and splits meaningful content from the input string.
     *
     * This function removes leading whitespace and splits the remaining content into a QStringList
     * using space (" ") as the delimiter, ignoring empty parts.
     *
     * @param data The input string that contains the command.
     * @return QStringList A list of extracted words from the input string. If no valid content is found,
     *         an empty list is returned.
     *
     * @note The function ensures that it does not return `void` by always returning a valid QStringList.
     */
    QStringList getContent(const QString& data) {
        QRegularExpression regex(R"(^(\s*)(\S.*)$)");
        QRegularExpressionMatch match = regex.match(data);
        if (!match.hasMatch()) return QStringList();
        QString content = match.captured(2);
        return content.split(" ", Qt::SkipEmptyParts);
    }

protected:
    void closeEvent(QCloseEvent *event) override {
        QDialog::closeEvent(event);
    }
};

#endif // DIALOGBASE_H
