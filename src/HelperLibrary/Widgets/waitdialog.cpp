#include "waitdialog.h"
#include "ui_waitdialog.h"

WaitDialog::WaitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Tool);
    setWindowFlag(Qt::WindowCloseButtonHint, false);

    startTimer(1000);
    m_startTime = QTime::currentTime();
    setElapsed(0);
}

WaitDialog::~WaitDialog()
{
    delete ui;
}

void WaitDialog::setText(const QString &_text)
{
    ui->label_2->setText(_text);
}

void WaitDialog::showAfter(int _ms)
{
    QTimer::singleShot(_ms, this, &WaitDialog::show);
}

void WaitDialog::setElapsed(int _sec)
{
    QTime time(0,0,0);
    time = time.addSecs(_sec);
    ui->label->setText(tr("Elapsed:") + " " + time.toString("mm:ss"));
}


void WaitDialog::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    setElapsed(m_startTime.secsTo(QTime::currentTime()));
}


void WaitDialog::keyPressEvent(QKeyEvent *event)
{
    if(event->key() != Qt::Key_Escape)
    {
        QDialog::keyPressEvent(event);
    }
}
