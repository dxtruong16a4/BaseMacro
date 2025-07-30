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
     * @brief Extracts and splits meaningful content from the input string with optional grouping.
     *
     * This function trims leading whitespace and splits the remaining content by spaces,
     * ignoring empty parts. If the `parts` parameter is specified and the input contains
     * more than `parts` tokens, the remaining tokens are joined together as the final part.
     *
     * This is useful for parsing command strings where the last argument (e.g., a window title)
     * may contain spaces and should be preserved as one string.
     *
     * @param data The input command string.
     * @param parts (Optional) The maximum number of parts to split. If set and the actual number of parts
     *              exceeds this, the remaining parts will be combined into one.
     *              If parts <= 0, no grouping is applied and a full split is returned.
     * @return QStringList A list of extracted parts from the string.
     */
    QStringList getContent(const QString& data, int parts = -1) {
        QRegularExpression regex(R"(^(\s*)(\S.*)$)");
        QRegularExpressionMatch match = regex.match(data);
        if (!match.hasMatch()) return QStringList();
    
        QString content = match.captured(2);
        QStringList tokens = content.split(" ", Qt::SkipEmptyParts);
    
        if (parts > 0 && tokens.size() > parts) {
            QStringList head = tokens.mid(0, parts - 1);
            QString tail = tokens.mid(parts - 1).join(" ");
            head << tail;
            return head;
        }
    
        return tokens;
    }

protected:
    void closeEvent(QCloseEvent *event) override {
        QDialog::closeEvent(event);
    }
};

#endif // DIALOGBASE_H
