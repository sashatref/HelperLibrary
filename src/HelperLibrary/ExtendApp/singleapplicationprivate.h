#pragma once

#include "extendapp.h"

class QLocalServer;

class SingleApplicationPrivate
{
public:
    SingleApplicationPrivate(ExtendApp *_app, const QString &_uniqueName);
    ~SingleApplicationPrivate();

    void initSingleApplication();

    bool m_isRunning;
    QString m_uniqueName;


#ifdef Q_OS_WIN
    HANDLE m_mutex;
#endif
    QLocalServer *m_server;
    ExtendApp *m_app;
};

