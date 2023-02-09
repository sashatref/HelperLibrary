#pragma once

#include <QDialog>
#include <QFuture>
#include <QTime>

#include "../export.h"

namespace Ui {
class ProgressDialog;
}

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT ProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressDialog(const QString &_text = "");
    ~ProgressDialog();

    void setCancelButtonVisible(bool _v);
    void watchForFuture(const QFuture<void> &_future);

public slots:
    void futureFinished();

signals:
    void cancelClicked();

protected:
    virtual void changeEvent(QEvent *) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void timerEvent(QTimerEvent *event) override;

    void retranslate();

private slots:
    void on_cancelButton_clicked();

private:
    void setElapsed(int _sec);

    Ui::ProgressDialog *ui;
    QFutureWatcher<void> *m_watcher;
    QTime m_startTime;
};

}
