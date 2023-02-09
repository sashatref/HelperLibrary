#include "progressdialog.h"
#include "ui_progressdialog.h"

#include <QMovie>
#include <QFutureWatcher>

namespace HelperLibraryNS
{

ProgressDialog::ProgressDialog(const QString &_text) :
    QDialog(0),
    ui(new Ui::ProgressDialog),
    m_watcher(new QFutureWatcher<void>())
{
    ui->setupUi(this);

    setWindowFlags(Qt::Tool);
    setWindowFlag(Qt::WindowCloseButtonHint, false);

    retranslate();

    startTimer(1000);
    m_startTime = QTime::currentTime();
    setElapsed(0);

    QMovie *movie = new QMovie(":/Images/CustomStyle/waitGif.gif", QByteArray(), this);
    ui->animatedLabel->setMovie(movie);
    movie->setScaledSize(QSize(100, 100));
    movie->start();

    connect(m_watcher, &QFutureWatcher<void>::finished, this, &ProgressDialog::futureFinished);

    ui->titleLabel->setText(_text);
    if(_text.isEmpty())
    {
        ui->titleLabel->hide();
    } else
    {
        setWindowTitle(_text);
    }
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
    delete m_watcher;
}

void ProgressDialog::setCancelButtonVisible(bool _v)
{
    ui->cancelButton->setVisible(_v);
}

void ProgressDialog::watchForFuture(const QFuture<void> &_future)
{
    m_watcher->setFuture(_future);
    exec();
}


void ProgressDialog::changeEvent(QEvent *e)
{
    switch(e->type())
    {
    case QEvent::LanguageChange:
        retranslate();
        break;
    default:
        break;
    }

    QDialog::changeEvent(e);
}

void ProgressDialog::retranslate()
{
    ui->retranslateUi(this);

    setWindowTitle(tr("Загрузка данных"));
}

void ProgressDialog::futureFinished()
{
    close();
}

void ProgressDialog::setElapsed(int _sec)
{
    QTime time(0,0,0);
    time = time.addSecs(_sec);
    ui->label->setText(tr("Elapsed:") + " " + time.toString("mm:ss"));
}


void ProgressDialog::keyPressEvent(QKeyEvent *event)
{
    if(event->key() != Qt::Key_Escape)
    {
        QDialog::keyPressEvent(event);
    }
}


void ProgressDialog::timerEvent(QTimerEvent * /*event*/)
{
    setElapsed(m_startTime.secsTo(QTime::currentTime()));
}

void ProgressDialog::on_cancelButton_clicked()
{
    emit cancelClicked();
}

}


