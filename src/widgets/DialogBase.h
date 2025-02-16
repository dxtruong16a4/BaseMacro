#ifndef DIALOGBASE_H
#define DIALOGBASE_H

#include <QDialog>

class DialogBase : public QDialog
{
    Q_OBJECT
public:
    explicit DialogBase(QWidget *parent = nullptr) : QDialog(parent) {}
    virtual ~DialogBase() {}

    virtual void closeEvent(QCloseEvent *event) override {}
};

#endif // DIALOGBASE_H
