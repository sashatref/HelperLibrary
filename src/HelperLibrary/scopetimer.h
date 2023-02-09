#pragma once

#include <QElapsedTimer>
#include <QString>
#include <QDebug>
#include "export.h"

class HELPERLIBRARY_EXPORT ScopeTimer
{
public:
    ScopeTimer(const QString &_name);
    ~ScopeTimer();

private:
    QElapsedTimer m_timer;
    QString m_name;
};


class HELPERLIBRARY_EXPORT LongTaskTimer
{
public:
    LongTaskTimer(int _minDelayMs, const QString &_text);
    ~LongTaskTimer();

private:
    QElapsedTimer m_timer;
    QString m_name;
    int m_delay;
};

