#include "project_pch.h"
#include "myprogressdialog.h"


MyProgressDialog::MyProgressDialog(QWidget *parent, const QString &_label, const QString &_title, const QString &_cancelText, int minimumDuration) :
    QProgressDialog(parent)
{
    setLabelText(_label);
    setCancelButtonText(_cancelText);
    setWindowTitle(_title);
    setValue(0);
    setMaximum(0);
    setWindowFlags(Qt::Window);
    //setWindowFlags(Qt::ToolTip);
    setMinimumDuration(minimumDuration);
    WidgetHelper::setWidgetOnScreenCenter(this, parent, 250, 100);
    cancel();
}

MyProgressDialog *MyProgressDialog::createContinuousDialog(QWidget *parent, const QString &_label, const QString &_title, const QString &_cancelText, int minimumDuration)
{
    MyProgressDialog *dialog = new MyProgressDialog(parent, _label, _title, _cancelText, minimumDuration);
    dialog->findChild<QPushButton*>()->hide();
    dialog->findChild<QProgressBar*>()->setTextVisible(false);
    return dialog;
}

void MyProgressDialog::onUpdateStarted()
{
    open();
}

void MyProgressDialog::onUpdateProgress(int _current, int _total)
{
    this->setMaximum(_total);
    this->setValue(_current);
}

void MyProgressDialog::onUpdateFinished()
{
    delete this;
}
