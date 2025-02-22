#ifndef DIALOGABOUT_H
#define DIALOGABOUT_H

#include "../core/DialogBase.h"
#include "../core/DefaultConstants.h"

#include <memory>
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
    void setData(const QString& data) override;
    void editItem(QListWidgetItem *item) override;

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
