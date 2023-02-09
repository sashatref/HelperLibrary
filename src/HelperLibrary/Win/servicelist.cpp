#include "servicelist.h"
#include "../Exceptions/userexception.h"
#include "winapihelper.h"

ServiceList::ServiceList(const QString &_hostAddress):
    m_serviceMap(),
    m_hostAddr(_hostAddress),
    m_scManager(0)
{

}

ServiceList::~ServiceList()
{
    deInit();
}

void ServiceList::init(ServiceList::ScManagerAccesses _accesses)
{
    using namespace HelperLibrary;

    if(m_scManager) return;

    m_scManager = OpenSCManagerA(m_hostAddr.toStdString().c_str(), NULL, _accesses);

    if(!m_scManager)
    {
        throw UserExceptions::BaseException(QString("Error while connection to SCManager on host <%1> | %2")
                                            .arg(m_hostAddr)
                                            .arg(WinApiHelper::getLastErrorMsg()), false);
    }
}

void ServiceList::deInit()
{
    for(auto it = m_serviceMap.begin(); it != m_serviceMap.end(); ++it)
    {
        delete it.value();
    }
    m_serviceMap.clear();

    if(m_scManager)
    {
        CloseServiceHandle(m_scManager);
        m_scManager = 0;
    }
}


void ServiceList::enumAllServices()
{
    throw HelperLibrary::UserExceptions::NotImplementedException(Q_FUNC_INFO);
}

QMap<QString, ServiceInfo *> ServiceList::getServiceMap()
{
    return m_serviceMap;
}

ServiceInfo *ServiceList::getService(const QString &_serviceName)
{
    if(m_serviceMap.contains(_serviceName))
    {
        return m_serviceMap[_serviceName];
    }

    ServiceInfo *ptr = new ServiceInfo(_serviceName, this);
    m_serviceMap[_serviceName] = ptr;
    return ptr;
}
