#include "winapiqt.h"
#include "handleptr.h"
#include "../functions.h"
#include "Exceptions/userexception.h"

#include <QHostInfo>
#include <QTextCodec>


namespace HelperLibraryNS
{

struct CallbackData
{
    QVariantMap input;
    QVariantMap output;
};

//int __stdcall OnEnumWindowShow(HWND hwnd, LPARAM lParam)
//{
//    CallbackData *data = reinterpret_cast<CallbackData*>(lParam);
//    const QString processName = data->input["processName"].toString();

//    DWORD dwProcessID;
//    if (GetWindowThreadProcessId(hwnd, &dwProcessID))
//    {
//        HandlePtr hProcess(OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID));
//        if (hProcess)
//        {
//            const int buffSize = 4096;
//            TCHAR buff[buffSize] = { 0 };
//            if (WinApiFuncLoader::GetModuleFileNameExW(hProcess.get(), NULL, buff, buffSize))
//            {
//                const QString sModuleName = QString::fromWCharArray(buff);

//                if (sModuleName.indexOf(processName, Qt::CaseInsensitive) != -1)
//                {
//                    RECT rect;
//                    GetWindowRect(hwnd, &rect);

//                    data->output["rect"] = QRect(rect.left,
//                                                 rect.top,
//                                                 rect.right - rect.left,
//                                                 rect.bottom - rect.top);

//                    return false;
//                }
//            }
//        }
//    }

//    return true;
//}

QRect WinApiQt::findWindowRect(const QString &_className, const QString &_windowName)
{
    HWND win = findWindow(_className, _windowName);
    return getWindowRect(win);
}

HWND WinApiQt::findWindow(const QString &_className, const QString &_windowName)
{
    const char *classStr = 0;
    const char *windowStr = 0;

    QByteArray classData;
    QByteArray windowData;

    if (!_className.isEmpty())
    {
        classData = _className.toUtf8();
        classStr = classData.data();
    }

    if (!_windowName.isEmpty())
    {
        windowData = _windowName.toUtf8();
        windowStr = windowData.data();
    }

    return FindWindowA(classStr, windowStr);
}

QRect WinApiQt::getWindowRect(HWND _hWnd)
{
    RECT rect = { };
    GetWindowRect(_hWnd, &rect);
    return QRect(rect.left,
                 rect.top,
                 rect.right - rect.left,
                 rect.bottom - rect.top);
}

QString WinApiQt::getLastErrorMsg()
{
    return parseError(GetLastError());
}

QString WinApiQt::getComputerName()
{
    DWORD iSize = 256;
    char cComputerName[256];
    GetComputerNameA(cComputerName, &iSize);
    return QString(cComputerName).toUpper();
}

QString WinApiQt::parseError(unsigned long _error)
{
    LPWSTR bufPtr = NULL;
    DWORD err = _error;
    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                   FORMAT_MESSAGE_FROM_SYSTEM |
                   FORMAT_MESSAGE_IGNORE_INSERTS,
                   NULL, err, 0, (LPWSTR)&bufPtr, 0, NULL);
    const QString result =
            (bufPtr) ? QString::fromWCharArray(bufPtr).trimmed() : QString("Unknown Error %1").arg((int)err);
    LocalFree(bufPtr);
    return result;
}

MEMORYSTATUSEX WinApiQt::getRamInfo()
{
    MEMORYSTATUSEX memory_status = {};
    memory_status.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memory_status);
    return memory_status;
}

void WinApiQt::openFileInExplorer(const QString &_filePath)
{
    const QString winApiFilePath = QDir::toNativeSeparators(_filePath);

    QProcess::execute("explorer.exe", QStringList() << QString("/select,%1").arg(winApiFilePath));
}

void WinApiQt::openFolderInExplorer(const QString &_folderPath)
{
    const QString winApiFolderPath = QDir::toNativeSeparators(_folderPath);

    QProcess::execute("explorer.exe", QStringList() << QString("/root,%1").arg(winApiFolderPath));
}

QString WinApiQt::getNetAddress(const QString &_inAddr)
{
    QHostInfo info = QHostInfo::fromName(_inAddr);
    if(info.addresses().size())
    {
        return info.addresses().first().toString();
    }
    return QString();
}

void WinApiQt::pingExternal(const QString &_addr)
{
    QProcess process;
    process.setReadChannel(QProcess::StandardOutput);
    process.start("ping", QStringList() << _addr);
    process.waitForFinished(10000);

    if(process.exitCode() != 0)
    {
        QString errText;
        QTextStream stream(&errText);
        stream.setCodec(QTextCodec::codecForName("Windows-866"));
        stream << process.readAll();

        throw HelperLibrary::UserExceptions::BaseException(QString("Error while ping host [%1] | %2")
                                                           .arg(_addr)
                                                           .arg(errText));
    }
}

}
