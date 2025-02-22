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

protected:
    void closeEvent(QCloseEvent *event) override {
        QDialog::closeEvent(event);
    }
};

#endif // DIALOGBASE_H
