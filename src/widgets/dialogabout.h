#ifndef DIALOGABOUT_H
#define DIALOGABOUT_H

#include "DialogBase.h"

#include <memory>
#include <QDialog>
#include <QCloseEvent>
#include <QDesktopServices>
#include <QUrl>

namespace Ui {
class DialogAbout;
}

class DialogAbout : public DialogBase
{
    Q_OBJECT

public:
    ~DialogAbout();
    static DialogAbout* getInstance();

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
