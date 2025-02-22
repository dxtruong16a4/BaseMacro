#ifndef DIALOGHOWTOUSE_H
#define DIALOGHOWTOUSE_H

#include "../core/DialogBase.h"

namespace Ui {
class DialogHowToUse;
}

class DialogHowToUse : public DialogBase
{
    Q_OBJECT

public:
    static DialogHowToUse* getInstance();
    ~DialogHowToUse();
    void editItem(QListWidgetItem *item) override;
    void setData(const QString& data) override;

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    explicit DialogHowToUse(QWidget *parent = nullptr);
    Ui::DialogHowToUse *ui;
    static std::unique_ptr<DialogHowToUse> uniqueInstance;
    friend std::unique_ptr<DialogHowToUse> std::make_unique<DialogHowToUse>();
};

#endif // DIALOGHOWTOUSE_H
