#ifndef DIALOGTIPS_H
#define DIALOGTIPS_H

#include "../core/DialogBase.h"

namespace Ui {
class DialogTips;
}

class DialogTips : public DialogBase
{
    Q_OBJECT

public:
    static DialogTips* getInstance();
    ~DialogTips();
    void editItem(QListWidgetItem *item) override;
    void setData(const QString& data) override;

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    explicit DialogTips(QWidget *parent = nullptr);
    Ui::DialogTips *ui;
    static std::unique_ptr<DialogTips> uniqueInstance;
    friend std::unique_ptr<DialogTips> std::make_unique<DialogTips>();
};

#endif // DIALOGTIPS_H
