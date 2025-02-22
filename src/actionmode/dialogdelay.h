#ifndef DIALOGDELAY_H
#define DIALOGDELAY_H

#include "../core/DialogBase.h"
#include "../widgets/macroeditor.h"

namespace Ui {
class DialogDelay;
}

class DialogDelay : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDelay(QWidget *parent = nullptr);
    ~DialogDelay();

private slots:
    void on_sbTotal_valueChanged(int arg1);

    void on_sbMinutes_valueChanged(int arg1);

    void on_sbSeconds_valueChanged(int arg1);

    void on_sbMiliseconds_textChanged(const QString &arg1);

private:
    Ui::DialogDelay *ui;
};

#endif // DIALOGDELAY_H
