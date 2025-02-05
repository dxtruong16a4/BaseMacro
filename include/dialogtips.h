#ifndef DIALOGTIPS_H
#define DIALOGTIPS_H

#include "DialogBase.h"

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class DialogTips;
}

class DialogTips : public DialogBase
{
    Q_OBJECT

public:
    ~DialogTips();
    static DialogTips* getInstance();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    explicit DialogTips(QWidget *parent = nullptr);
    Ui::DialogTips *ui;
    static DialogTips* uniqueInstance;
};

#endif // DIALOGTIPS_H
