#include "serviceinfo.h"
#include "../Exceptions/userexception.h"
#include "../releaseassert.h"
#include "../scopetimer.h"
#include "../functions.h"
#include "winapihelper.h"

ServiceInfo::ServiceInfo(const QString &_serviceName, ServiceList *_servicelist):
    m_serviceName(_serviceName),
    m_serviceList(_servicelist),
    m_serviceHandle(0)
{

}

ServiceInfo::~ServiceInfo()
{
    deInit();
}

void ServiceInfo::init(ServiceInfo::ServiceAccesses _accesses)
{
    using namespace HelperLibrary;

    if(m_serviceHandle) return;

    if(!m_serviceList->m_scManager)
    {
        throw UserExceptions::BaseException(QString("SCManager not connected for host <%1>")
                                            .arg(m_serviceList->m_hostAddr), false);
    }

    m_serviceHandle = OpenServiceA(m_serviceList->m_scManager, m_serviceName.toStdString().c_str(), _accesses);

    if(!m_serviceHandle)
    {
        throw UserExceptions::BaseException(QString("Error while OpenService <%1> on host <%2>")
                                            .arg(m_serviceName)
                                            .arg(m_serviceList->m_hostAddr), false);
    }
}

void ServiceInfo::deInit()
{
    if(m_serviceHandle)
    {
        CloseServiceHandle(m_serviceHandle);
        m_serviceHandle = 0;
    }
}

void ServiceInfo::start()
{
    using namespace HelperLibrary;

    if(isRunning()) return;

    SERVICE_STATUS sStatus = queryStatus();

    if (!StartServiceA(m_serviceHandle, // handle to service
                      0, // number of arguments
                      NULL)) // no arguments
    {
        throw UserExceptions::BaseException(QString("Couldn't start service %1 | %2")
                                            .arg(m_serviceName)
                                            .arg(WinApiHelper::getLastErrorMsg()), false);
    }

    DWORD dwStartTickCount = 0;
    int dwWaitTime;
    DWORD dwOldCheckPoint = sStatus.dwCheckPoint;

    do
    {
        dwWaitTime = sStatus.dwWaitHint / 10;
        Numerics::fixValue(dwWaitTime, 1000, 10000);

        Sleep(dwWaitTime);

        sStatus = queryStatus();

        if (sStatus.dwCheckPoint > dwOldCheckPoint)
        {
            // The service is making progress.

            dwStartTickCount = GetTickCount();
            dwOldCheckPoint = sStatus.dwCheckPoint;
        }
        else
        {
            if (GetTickCount() - dwStartTickCount > sStatus.dwWaitHint)
            {
                // No progress made within the wait hint
                break;
            }
        }
    }
    while (sStatus.dwCurrentState == ssStartPending);

    if (sStatus.dwCurrentState != ssRunning)
    {
        throw UserExceptions::BaseException(QString("Error while service running <%1> | %2")
                                            .arg(m_serviceName)
                                            .arg(WinApiHelper::getLastErrorMsg()), false);
    }
}

void ServiceInfo::stop()
{
    using namespace HelperLibrary;

    if(!isRunning()) return;

    SERVICE_STATUS ssStatus;

    if (!ControlService(m_serviceHandle, SERVICE_CONTROL_STOP, &ssStatus))
    {
        throw UserExceptions::BaseException(QString("Couldn't stop service %1 | %2")
                                            .arg(m_serviceName)
                                            .arg(WinApiHelper::getLastErrorMsg()), false);
    }
}

void ServiceInfo::disable()
{
    stop();
    setStartType(stDisabled);
}

void ServiceInfo::enableManual()
{
    setStartType(stDemandStart);
}

void ServiceInfo::enableAtomatic()
{
    setStartType(ServiceInfo::stAutoStart);
}

void ServiceInfo::setStartType(ServiceInfo::StartType _startType)
{
    using namespace HelperLibrary;

    checkPtrs();

    if (!ChangeServiceConfigA(m_serviceHandle,
                              SERVICE_NO_CHANGE,
                              _startType,
                              SERVICE_NO_CHANGE, 0, 0, 0, 0, 0, 0, 0))
    {
        throw UserExceptions::BaseException(QString("Couldn't set service <%1> startType to <%2> | %3")
                                            .arg(m_serviceName)
                                            .arg(Text::enumToString(_startType, &staticMetaObject, "StartType"))
                                            .arg(WinApiHelper::getLastErrorMsg()), false);
    }
}

bool ServiceInfo::isRunning() const
{
    return queryStatus().dwCurrentState == ssRunning;
}

ServiceInfo::ServiceState ServiceInfo::getCurrentState() const
{
    return static_cast<ServiceInfo::ServiceState>(queryStatus().dwCurrentState);
}

ServiceInfo::StartType ServiceInfo::getCurrentStartType() const
{
    return static_cast<StartType>(queryConfig().dwStartType);
}

SERVICE_STATUS ServiceInfo::queryStatus() const
{
    using namespace HelperLibrary;

    //ScopeTimer timer("Query status");

    checkPtrs();

    SERVICE_STATUS ssStatus;

    if (!QueryServiceStatus(m_serviceHandle, &ssStatus))
    {
        throw UserExceptions::BaseException(QString("Error while quering service <%1> on host <%2> | %3")
                                            .arg(m_serviceName)
                                            .arg(m_serviceList->m_hostAddr)
                                            .arg(WinApiHelper::getLastErrorMsg()), false);
    }

    return ssStatus;
}

QUERY_SERVICE_CONFIGA ServiceInfo::queryConfig() const
{
    using namespace HelperLibrary;

    checkPtrs();

    QUERY_SERVICE_CONFIGA sConfig;
    DWORD dwBytesNeeded, cbBufSize = 0, dwError;
    LPQUERY_SERVICE_CONFIGA lpsc = 0;

    if( !QueryServiceConfigA(m_serviceHandle, NULL, 0, &dwBytesNeeded))
    {
        dwError = GetLastError();
        if( ERROR_INSUFFICIENT_BUFFER == dwError )
        {
            cbBufSize = dwBytesNeeded;
            lpsc = static_cast<LPQUERY_SERVICE_CONFIGA>(LocalAlloc(LMEM_FIXED, cbBufSize));
        }
        else
        {
            throw UserExceptions::BaseException(QString("Error while quering config service <%1> on host <%2> | %3")
                                                .arg(m_serviceName)
                                                .arg(m_serviceList->m_hostAddr)
                                                .arg(WinApiHelper::parseError(dwError)), false);
        }
    }

    if( !QueryServiceConfigA(m_serviceHandle, lpsc, cbBufSize, &dwBytesNeeded))
    {
        throw UserExceptions::BaseException(QString("Error while quering config service <%1> on host <%2> | %3")
                                            .arg(m_serviceName)
                                            .arg(m_serviceList->m_hostAddr)
                                            .arg(WinApiHelper::getLastErrorMsg()), false);
    }

    sConfig = *lpsc;

    LocalFree(lpsc);

    return sConfig;
}






ServiceList *ServiceInfo::getServiceList()
{
    return m_serviceList;
}

QString ServiceInfo::getServiceDisplayName()
{
    using namespace HelperLibrary;

    checkPtrs();

    char displayName[256] = {0};
    DWORD buffSize = 256;

    if(!GetServiceDisplayNameA(m_serviceHandle, m_serviceName.toStdString().c_str(), displayName, &buffSize))
    {
        throw UserExceptions::BaseException(QString("Error during 'GetServiceDisplayName' for service <%1> | %2")
                                            .arg(m_serviceName)
                                            .arg(WinApiHelper::getLastErrorMsg()));
    }

    return QString(displayName);
}

QString ServiceInfo::getHostAddress() const
{
    return m_serviceList->m_hostAddr;
}

QString ServiceInfo::getServiceName() const
{
    return m_serviceName;
}

void ServiceInfo::checkPtrs() const
{
    using namespace HelperLibrary;

    R_ASSERT(m_serviceList);

    if(!m_serviceList->m_scManager)
    {
        throw UserExceptions::BaseException(QString("SCManager not connected for host <%1>")
                                            .arg(m_serviceList->m_hostAddr), false);
    }

    if(!m_serviceHandle)
    {
        throw UserExceptions::BaseException(QString("Service <%1> not opened on host <%2>")
                                            .arg(m_serviceName)
                                            .arg(m_serviceList->m_hostAddr), false);
    }
}
