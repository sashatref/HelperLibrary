#include "singleapplicationprivate.h"

#include <QLocalServer>
#include <QLocalSocket>

SingleApplicationPrivate::SingleApplicationPrivate(ExtendApp *_app, const QString &_uniqueName):
    m_isRunning(false),
    m_uniqueName(_uniqueName),
#ifdef Q_OS_WIN
    m_mutex(0),
#endif
    m_server(0),
    m_app(_app)
{}

SingleApplicationPrivate::~SingleApplicationPrivate()
{
#ifdef Q_OS_WIN
    if(!m_isRunning)
    {
       ReleaseMutex(m_mutex);
    }
    CloseHandle(m_mutex);
#endif

    if(m_server) delete m_server;
}

void SingleApplicationPrivate::initSingleApplication()
{
#ifdef Q_OS_WIN
    if(m_uniqueName.isEmpty())
    {
        qCInfo(extendApp) << "Single Application: Unique name not specified. Disabled";
        return;
    } else
    {
        qCInfo(extendApp) << QString("Single Application: Registered for name <%1>").arg(m_uniqueName);
    }

    const QString mutexName = QString("Global\\%1_QtSingleApplicationMutex").arg(m_uniqueName);
    m_mutex = CreateMutexA(NULL, FALSE, mutexName.toStdString().c_str());
    if(GetLastError() == ERROR_ALREADY_EXISTS)
    {
        m_isRunning = true;
        {
            QLocalSocket socket;
            socket.connectToServer(m_uniqueName + "_QtLocalServer");
            socket.close();
        }
    } else
    {
        m_isRunning = false;
        m_server = new QLocalServer();
        m_server->listen(m_uniqueName + "_QtLocalServer");
        QObject::connect(m_server, &QLocalServer::newConnection, m_app, &ExtendApp::onAnotherInstanceLaunch);
        m_server->waitForNewConnection();
    }

#else
    qCWarning(extendApp) << "SingleApplication not working on this this system";
    qCWarning(extendApp) << Q_FUNC_INFO;
#endif
}

