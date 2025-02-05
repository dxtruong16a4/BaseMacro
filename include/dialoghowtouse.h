#ifndef DIALOGHOWTOUSE_H
#define DIALOGHOWTOUSE_H

#include "DialogBase.h"

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class DialogHowToUse;
}

class DialogHowToUse : public DialogBase
{
    Q_OBJECT

public:
    ~DialogHowToUse();
    static DialogHowToUse* getInstance();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    explicit DialogHowToUse(QWidget *parent = nullptr);
    Ui::DialogHowToUse *ui;
    static DialogHowToUse* uniqueInstance;
};

#endif // DIALOGHOWTOUSE_H
