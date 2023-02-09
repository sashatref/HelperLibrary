#include "winapihelper.h"

#include "Exceptions/userexception.h"
#include "handleptr.h"
#include "winapiqt.h"

struct WindowInfo
{
    QRect rect;
    QString processName;
    bool result = false;
};


WinApiHelper::WinApiHelper() :
    m_window        (NULL)
{

}



bool WinApiHelper::findWindow(const QString &_className, const QString &_windowName)
{
    const char *classStr = 0;
    const char *windowStr = 0;

    if(!_className.isEmpty())
    {
        classStr = _className.toStdString().c_str();
    }

    if(!_windowName.isEmpty())
    {
        windowStr = _windowName.toStdString().c_str();
    }

    m_window = FindWindowA(classStr, windowStr);

    return m_window;
}

QString WinApiHelper::parseError(ulong _error)
{
    return HelperLibraryNS::WinApiQt::parseError(_error);
}

QString WinApiHelper::getLastErrorMsg()
{
    return HelperLibraryNS::WinApiQt::getLastErrorMsg();
}

void WinApiHelper::pressDownKey(Qt::Key _key)
{
    keybd_event(mapKeyToWinApi(_key), 0, KEYEVENTF_KEYUP, 0);
}

void WinApiHelper::pressUpKey(Qt::Key _key)
{
    keybd_event(mapKeyToWinApi(_key), 0, 0, 0);
}

void WinApiHelper::clickKey(Qt::Key _key)
{
    pressDownKey(_key);
    pressUpKey(_key);
}

void WinApiHelper::clickKeyGroup(QList<Qt::Key> _keys)
{
    for(int i = 0, count = _keys.size() ; i < count; i++)
    {
        pressDownKey(_keys.at(i));
    }

    for(int i = _keys.size() - 1 ; i > -1; i--)
    {
        pressUpKey(_keys.at(i));
    }
}

HWND WinApiHelper::getWindowWnd() const
{
    return m_window;
}

int WinApiHelper::mapKeyToWinApi(Qt::Key _key)
{
    using namespace HelperLibrary::UserExceptions;

    int result = -1;

    switch(_key)
    {
    case Qt::Key_Control:
        result = VK_CONTROL;
        break;
    case Qt::Key_Tab:
        result = VK_TAB;
        break;
    case Qt::Key_Return:
        result = VK_RETURN;
        break;
    case Qt::Key_Shift:
        result = VK_SHIFT;
        break;
    case Qt::Key_E:
        result = 0x45;
        break;
    case Qt::Key_W:
        result = 0x57;
        break;

    default:
        throw BaseException("Converter not implemented for this key");
    }

    return result;
}

QString WinApiHelper::getComputerName()
{
    return HelperLibraryNS::WinApiQt::getComputerName();
}

bool WinApiHelper::setComputerName(const QString &_name)
{
    if(!SetComputerNameExW(ComputerNamePhysicalDnsHostname, _name.toStdWString().c_str()))
    {
        qDebug() << GetLastError();
        return false;
    }
    return true;
}

QString WinApiHelper::expandEnvironmentString(const QString &_path)
{
    char out[1024];
    ExpandEnvironmentStringsA(_path.toUtf8(), out, 1024);
    return QString(out);
}



QString qExpandEnv(const QString &_in)
{
    return WinApiHelper::expandEnvironmentString(_in);
}

void qExpandEnv(std::initializer_list<QString *> _arr)
{
    for(auto *it : _arr)
    {
        *it = qExpandEnv(*it);
    }
}
