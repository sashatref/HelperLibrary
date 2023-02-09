#pragma once

#include <QDialog>
#include <QTime>

#include "../export.h"

namespace Ui {
class WaitDialog;
}

class HELPERLIBRARY_EXPORT WaitDialog : public QDialog
{
    Q_OBJECT
public:
    explicit WaitDialog(QWidget *parent = nullptr);
    ~WaitDialog();

    void setText(const QString &_text);

    void showAfter(int _ms);

private:
    void setElapsed(int _sec);

    Ui::WaitDialog *ui;
    QTime m_startTime;

protected:
    virtual void timerEvent(QTimerEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
};
