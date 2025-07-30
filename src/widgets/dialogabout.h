#ifndef DIALOGABOUT_H
#define DIALOGABOUT_H

#include "../core/DefaultConstants.h"
#include "../core/DialogBase.h"

namespace Ui {
class DialogAbout;
}

class DialogAbout : public DialogBase
{
    Q_OBJECT

public:
    static DialogAbout* getInstance();
    ~DialogAbout();
    void editItem(QListWidgetItem *item) override;
    void setData(const QString& data) override;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_commandLinkButton_clicked();

private:
    explicit DialogAbout(QWidget *parent = nullptr);
    Ui::DialogAbout *ui;
    static std::unique_ptr<DialogAbout> uniqueInstance;
    friend std::unique_ptr<DialogAbout> std::make_unique<DialogAbout>();
};
#endif // DIALOGABOUT_H
