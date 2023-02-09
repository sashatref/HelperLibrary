#pragma once

#include <QString>

#include "../export.h"

class HELPERLIBRARY_EXPORT ShellHelper
{
public:

    /*!
     * \brief isExtSupported Указывает есть ли какая-то программа,
     * ассоциированная с указанным расширением файла
     * \param _fileExt .txt | .pdf
     * \return
     */
    static bool isExtSupported(const QString &_fileExt);

    /*!
     * \brief extProgramm Указывает путь к программе,
     * ассоциированной с указанным расширением файла
     * \param _fileExt .txt | .pdf
     * \return
     */
    static QString extProgrammHandler(const QString &_fileExt);

    //запустить программу с правами администратора
    static void invokeProgrammWithAdminRights(const QString &_path);

    //установка параметров электропитания
    static bool setPowerManagementParams();

    //установка параметров рабочей группы
    static bool setWorkGroupParams(const char *_workGroupName);

    static bool setUacParams();

    /*!
     * \brief setIpInterface
     * \param _lanName имя с центра управления сетями и общим доступом Local area network, Ethernet0, etc
     * \param _source static/dhcp
     * \param _addr     адрес 10.10.10.101
     * \param _mask     маска 255.255.255.0
     * \param _gateway  основной шлюх 10.10.10.1
     */

    static void setIpInterface(const QString &_lanName,
                               const QString &_source,
                               const QString &_addr,
                               const QString &_mask,
                               const QString &_gateway);

    static QStringList getIpInterfaces();

    static void disableIpv6();

    static void computerReboot(int _sleepSec);
};
