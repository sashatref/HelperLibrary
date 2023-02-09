#include "shellhelper.h"

#include <Shlwapi.h>


bool ShellHelper::isExtSupported(const QString &_fileExt)
{
    LPCWSTR wstr_ext = (const wchar_t*)_fileExt.utf16();

    wchar_t buff[1024];
    DWORD size = sizeof(buff);
    memset(&buff, '\0', sizeof(buff));

    HRESULT err = AssocQueryStringW(ASSOCF_INIT_IGNOREUNKNOWN, ASSOCSTR_EXECUTABLE, wstr_ext, NULL, buff, &size);

    if(S_OK == err)
    {
        return true;

        // Convert to wstring
        std::wstring wstring_data(&buff[0]);
        // To QString
        QString appPath = QString::fromStdWString(wstring_data);

        qDebug() << appPath;
    }

    return false;
}

QString ShellHelper::extProgrammHandler(const QString &_fileExt)
{
    LPCWSTR wstr_ext = (const wchar_t*)_fileExt.utf16();

    TCHAR buff[1024];
    DWORD size = sizeof(buff);
    memset(&buff, '\0', sizeof(buff));

    HRESULT err = AssocQueryString(ASSOCF_INIT_IGNOREUNKNOWN, ASSOCSTR_EXECUTABLE, wstr_ext, NULL, buff, &size);

    if(S_OK == err)
    {
        std::wstring wstring_data(&buff[0]);
        return QString::fromStdWString(wstring_data);
    }

    return QString();
}

void ShellHelper::invokeProgrammWithAdminRights(const QString &_path)
{
    ShellExecuteA(NULL, "runas", _path.toStdString().c_str(), NULL, NULL, SW_SHOWNORMAL);
}

bool ShellHelper::setPowerManagementParams()
{
    const char *path = "Powercfg.exe";
    ShellExecuteA(0,"open",path,"-x -monitor-timeout-ac 0",0,SW_HIDE);
    ShellExecuteA(0,"open",path,"-x -monitor-timeout-dc 0",0,SW_HIDE);
    ShellExecuteA(0,"open",path,"-x -disk-timeout-ac 0",0,SW_HIDE);
    ShellExecuteA(0,"open",path,"-x -disk-timeout-dc 0",0,SW_HIDE);
    ShellExecuteA(0,"open",path,"-x -standby-timeout-ac 0",0,SW_HIDE);
    ShellExecuteA(0,"open",path,"-x -standby-timeout-dc 0",0,SW_HIDE);

    return true;
}

bool ShellHelper::setWorkGroupParams(const char *_workGroupName)
{
    char cComputerName[256];
    DWORD iSize = 256;
    GetComputerNameA(cComputerName, &iSize);
    char parameters[256];
    strcpy(parameters, "MEMBER \\\\");
    strcat(parameters, cComputerName);
    strcat(parameters, " /JOINWORKGROUP ");
    strcat(parameters, _workGroupName);

    const char* path = "NetDom_86.exe";
    ShellExecuteA(0, "open", path, parameters, 0, SW_HIDE);

    return true;
}

bool ShellHelper::setUacParams()
{
    ShellExecuteA(0,"open", "reg","add HKLM\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /f /v EnableLUA /t REG_DWORD /d 0",0,SW_HIDE);
    return true;
}

void ShellHelper::setIpInterface(const QString &_lanName,
                                 const QString &_source,
                                 const QString &_addr,
                                 const QString &_mask,
                                 const QString &_gateway)
{
    QStringList args;
    args
            << "interface"
            << "ip"
            << "set"
            << "address"
            << QString("name=\"%1\"").arg(_lanName)
            << QString("source=%1").arg(_source);

    if(!_addr.isEmpty())
    {
        args << QString("addr=%1").arg(_addr);
    }

    if(!_mask.isEmpty())
    {
        args << QString("mask=%1").arg(_mask);
    }

    if(!_gateway.isEmpty())
    {
        args << QString("gateway=").arg(_gateway);
    }

    QProcess::startDetached("netsh", args);
}

//из командной строки парсит имена интерфейсов
QString parseInterfaceName(const QString &_rowText)
{
    QString res;

    const int spaceCount = 5;
    int currentSpace = 0;
    bool spaceBefore = false;

    for(int i = 0 ; i < _rowText.size(); i++)
    {
        if(_rowText.at(i) == ' ')
        {
            if(!spaceBefore)
            {
                currentSpace++;
                spaceBefore = true;
            }
        } else
        {
            if(currentSpace == spaceCount)
            {
                res = _rowText.right(_rowText.size() - i);
                return res;
            }

            spaceBefore = false;
        }
    }

    return res;
}


QStringList ShellHelper::getIpInterfaces()
{
    QStringList args;
    args
            << "interface"
            << "ip"
            << "show"
            << "interfaces";

    QProcess process;
    process.setReadChannel(QProcess::StandardOutput);
    process.start("netsh", args);
    process.waitForFinished(1000);

    QStringList resRows = QString(process.readAllStandardOutput()).split("\r\n");

    QStringList interfaceList;

    for(int i = 0 ; i < resRows.size(); i++)
    {
        interfaceList << parseInterfaceName(resRows.at(i));
    }

    return interfaceList;
}

void ShellHelper::disableIpv6()
{
    QStringList args;
    args
            << "netsh interface isatap set state disabled"
            << "netsh interface teredo set state disabled"
            << "netsh interface 6TO4 set state disabled";

    for(int i = 0 ; i < args.size(); i++)
    {
        QProcess process;
        process.setProgram("netsh");
        process.setNativeArguments(args.at(i));
        process.start();
        process.waitForFinished(1000);
    }
}

void ShellHelper::computerReboot(int _sleepSec)
{
    QProcess::startDetached("shutdown", QStringList() << "/r" << "/t" << QString::number(_sleepSec));
}
