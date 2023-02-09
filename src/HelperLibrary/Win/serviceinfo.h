#pragma once

#include <QString>
#include <QMetaType>
#include "servicelist.h"
#include <Windows.h>

#include "../export.h"

class ServiceList;

/*!
 * \brief The ServiceInfo class
 * Класс Для управления сервисом windows
 * После создания класса, необходимо выполнить метод init c указанием требуемых прав доступа
 *
 * @code
 *
 *  try
    {
        ServiceList list("localhost");
        list.init();
        ServiceInfo *service = list.getService("MySQL56");
        service->init();
        qDebug() << service->getCurrentStartType();
        qDebug() << service->getServiceDisplayName();
        service->start();
    }catch(std::exception &e)
    {
        InfoWindow(e.what()).exec();
    }
 *
 */

class HELPERLIBRARY_EXPORT ServiceInfo
{
    Q_GADGET
public:
    enum ServiceAccess // права доступа
    {
        sQueryConfig            = 0x0001,
        sChangeConfig           = 0x0002,
        sQueryStatus            = 0x0004,
        sEnumerateDependents    = 0x0008,
        sStart                  = 0x0010,
        sStop                   = 0x0020,
        sPauseContinue          = 0x0040,
        sInterrogate            = 0x0080,
        sUserDefinedControl     = 0x0100,
        sAll                    =   sQueryConfig |
                                    sChangeConfig |
                                    sEnumerateDependents |
                                    sStart |
                                    sStop |
                                    sPauseContinue |
                                    sInterrogate |
                                    sUserDefinedControl
    };
    Q_ENUM(ServiceAccess)

    enum ServiceState   // состояние сервиса
    {
        ssContinuePending       = SERVICE_CONTINUE_PENDING,
        ssPausePending          = SERVICE_PAUSE_PENDING,
        ssPaused                = SERVICE_PAUSED,
        ssRunning               = SERVICE_RUNNING,
        ssStartPending          = SERVICE_START_PENDING,
        ssStopPending           = SERVICE_STOP_PENDING,
        ssStopped               = SERVICE_STOPPED
    };
    Q_ENUM(ServiceState)

    enum StartType      // тип запуска
    {
        stAutoStart             = SERVICE_AUTO_START,
        stBootStart             = SERVICE_BOOT_START,
        stDemandStart           = SERVICE_DEMAND_START,
        stDisabled              = SERVICE_DISABLED,
        stSystemStart           = SERVICE_SYSTEM_START
    };
    Q_ENUM(StartType)

    Q_DECLARE_FLAGS(ServiceAccesses, ServiceAccess)
    Q_FLAG(ServiceAccesses)

    void init(ServiceAccesses _accesses = sAll);    // инициализация
    void deInit();                                  // деинициализация

    ServiceState getCurrentState() const;           // текущее состояние службы
    bool isRunning() const;                         // запущена ли
    void start();                                   // запуск службы
    void stop();                                    // остановка службы
    void disable();                                 // Тип запуска -> Отключена
    void enableManual();                            // Тип запуска -> Вручную
    void enableAtomatic();                          // Тип запуска -> Автоматически

    void setStartType(StartType _startType);        // Установить тип запуска
    StartType getCurrentStartType() const;          // Получить текущий тип запуска

    ServiceList *getServiceList();                  // получить родительский список сервисов

    QString getServiceDisplayName();                // получить отображаемое имя сервиса

    QString getHostAddress() const;                 // получить адрес хоста
    QString getServiceName() const;                 // имя сервиса

private:
    void checkPtrs() const;                         // проверить проинициализированы ли SCManager и хэндл сервиса
    SERVICE_STATUS queryStatus() const;             // получить статус сервиса
    QUERY_SERVICE_CONFIGA queryConfig() const;      // получить конфиг сервиса

    friend class ServiceList;
    ServiceInfo(const QString &_serviceName, ServiceList *_servicelist);
    ~ServiceInfo();

    QString m_serviceName;                          ///< имя сервиса
    ServiceList *m_serviceList;                     ///< родительский список сервисов

    SC_HANDLE m_serviceHandle;                      ///< хэндл сервиса
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ServiceInfo::ServiceAccesses)
