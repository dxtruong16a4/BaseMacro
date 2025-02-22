#ifndef DIALOGHOWTOUSE_H
#define DIALOGHOWTOUSE_H

#include "../core/DialogBase.h"

#include <memory>
#include <QCloseEvent>
#include <QDialog>

namespace Ui {
class DialogHowToUse;
}

class DialogHowToUse : public DialogBase
{
    Q_OBJECT

public:
    ~DialogHowToUse();
    static DialogHowToUse* getInstance();
    void setData(const QString& data) override;
    void editItem(QListWidgetItem *item) override;

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    explicit DialogHowToUse(QWidget *parent = nullptr);
    Ui::DialogHowToUse *ui;
    static std::unique_ptr<DialogHowToUse> uniqueInstance;
    friend std::unique_ptr<DialogHowToUse> std::make_unique<DialogHowToUse>();
};

#endif // DIALOGHOWTOUSE_H
