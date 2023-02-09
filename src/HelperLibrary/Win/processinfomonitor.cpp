#include "processinfomonitor.h"
#include "ui_processinfomonitor.h"
#include "../functions.h"

#include "processinfo.h"


ProcessInfoMonitor::ProcessInfoMonitor(QWidget *parent) :
    ExtendedWidget  (parent),
    ui              (new Ui::ProcessInfoMonitor)
{
    ui->setupUi(this);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &ProcessInfoMonitor::timedoutSlot);
    m_timer->setInterval(500);
    m_timer->start();

    initAll();

    updateView();
}

ProcessInfoMonitor::~ProcessInfoMonitor()
{
    delete ui;
}

void ProcessInfoMonitor::timedoutSlot()
{
    updateView();
}


void ProcessInfoMonitor::loadState(const LayoutSaver &_saver)
{
    _saver.loadGeometry(this, "g");
    _saver.load(ui->updateIntervalSpinbox, "updateInterval");
}

void ProcessInfoMonitor::saveState(LayoutSaver &_saver) const
{
    _saver.saveGeometry(this, "g");
    _saver.save(ui->updateIntervalSpinbox, "updateInterval");
}

void ProcessInfoMonitor::updateLanguage()
{
    ui->retranslateUi(this);
}

void ProcessInfoMonitor::updateStyle()
{
}

void ProcessInfoMonitor::initUiComponets()
{
    ui->processPIDLabel->setText(QString::number(ProcessInfo::currentPID()));
}

void ProcessInfoMonitor::initConnections()
{
}

void ProcessInfoMonitor::on_updateIntervalSpinbox_valueChanged(int arg1)
{
    m_timer->setInterval(arg1);
}

QString makeMemoryText(qint64 _size)
{
    return Text::fileSizeToString(_size);
}

void ProcessInfoMonitor::updateView()
{
    ProcessInfo pInfo = ProcessInfo::current();

    ui->currentRamLabel->setText(makeMemoryText(pInfo.currentUsedRam));
    ui->maxRamLabel->setText(makeMemoryText(pInfo.maxUsedRam));
    ui->threadCountLabel->setText(QString::number(ProcessInfo::getThreadList().size()));
    ui->lastUpdateTimeLabel->setText(QTime::currentTime().toString("hh:mm:ss"));
}
