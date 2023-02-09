#pragma once

#include "../export.h"
#include "serviceinfo.h"

#include <QList>
#include <QMap>
#include <Windows.h>
#include <QObject>

/*!
 *  Класс для управления сервисами на компьютере по заданному адресу.
 *
 * @code
 *  try
    {
        ServiceList list("localhost");
        list.init();

        ServiceInfo *service = list.getService("MySQL56");
        service->init();
        qDebug() << service->getCurrentStartType();
        service->start();

    }catch(std::exception &e)
    {
        InfoWindow(e.what()).exec();
    }
 *
 *
 * После создания класса, необходимо выполнить метода init() с указанием требуемых прав доступа,
 * для инициализации SCManager
 */

class ServiceInfo;

class HELPERLIBRARY_EXPORT ServiceList
{
    Q_GADGET
public:
    friend class ServiceInfo;

    enum ScManagerAccess
    {
        scConnect               = 0x0001,
        scCreateService         = 0x0002,
        scEnumerateService      = 0x0004,
        scLock                  = 0x0008,
        scQueryLockStatus       = 0x0010,
        scModifyBoot            = 0x0020,
        scAll                   =   scConnect |
                                    scCreateService |
                                    scEnumerateService |
                                    scLock |
                                    scQueryLockStatus |
                                    scModifyBoot |
                                    STANDARD_RIGHTS_REQUIRED
    };

    Q_DECLARE_FLAGS(ScManagerAccesses, ScManagerAccess)
    Q_FLAG(ScManagerAccesses)

    ServiceList(const QString &_hostAddress = "localhost");

    ~ServiceList();

    void init(ScManagerAccesses _accesses = scAll);     ///< инициализация SCManager
    void deInit();                                      ///< деинициализация

    void enumAllServices();

    QMap<QString, ServiceInfo*> getServiceMap();        ///< получить карту сервисов

    ServiceInfo *getService(const QString &_serviceName);   ///< получить сервис с указанным именем

private:
    QMap<QString, ServiceInfo*> m_serviceMap;
    QString m_hostAddr;

    SC_HANDLE m_scManager;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ServiceList::ScManagerAccesses)

