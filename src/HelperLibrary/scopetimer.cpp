#include "scopetimer.h"



ScopeTimer::ScopeTimer(const QString &_name):
    m_name(_name)
{
    m_timer.start();
}

ScopeTimer::~ScopeTimer()
{
    qDebug() << QString("%1 | Elapsed: %2 ms")
                .arg(m_name)
                .arg(m_timer.elapsed());
}

LongTaskTimer::LongTaskTimer(int _minDelayMs, const QString &_text):
    m_name(_text),
    m_delay(_minDelayMs)
{
    m_timer.start();
}

LongTaskTimer::~LongTaskTimer()
{
    const int elapsed = m_timer.elapsed();

    if(elapsed > m_delay)
    {
        qDebug() << QString("%1 | Elapsed: %2 ms")
                    .arg(m_name)
                    .arg(elapsed);
    }
}
