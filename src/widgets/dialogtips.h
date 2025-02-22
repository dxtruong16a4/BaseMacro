#ifndef DIALOGTIPS_H
#define DIALOGTIPS_H

#include "../core/DialogBase.h"

#include <memory>
#include <QCloseEvent>
#include <QDialog>

namespace Ui {
class DialogTips;
}

class DialogTips : public DialogBase
{
    Q_OBJECT

public:
    ~DialogTips();
    static DialogTips* getInstance();
    void setData(const QString& data) override;
    void editItem(QListWidgetItem *item) override;

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    explicit DialogTips(QWidget *parent = nullptr);
    Ui::DialogTips *ui;
    static std::unique_ptr<DialogTips> uniqueInstance;
    friend std::unique_ptr<DialogTips> std::make_unique<DialogTips>();
};

#endif // DIALOGTIPS_H
