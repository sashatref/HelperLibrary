#pragma once

#include <exception>
#include <QString>
#include <QStringList>
#include <QException>
#include <stdexcept>

#include "../export.h"

namespace HelperLibrary
{

namespace UserExceptions
{

class HELPERLIBRARY_EXPORT BaseException : public std::runtime_error
{
public:
    BaseException(const QString &_text = "", bool _stackTrace = true);

    QStringList getStackTraceList() const;
    QString getText() const;

    friend QDebug HELPERLIBRARY_EXPORT operator<< (QDebug d, const BaseException &e);

private:
    QStringList m_stackTrace;
};



class HELPERLIBRARY_EXPORT ToObjectException : public BaseException
{
public:
    ToObjectException(const char *_typeName);
};

class HELPERLIBRARY_EXPORT ToIGadgetException : public BaseException
{
public:
    ToIGadgetException(const char *_typeName);
};

class HELPERLIBRARY_EXPORT NotImplementedException : public BaseException
{
public:
    NotImplementedException(const QString &_text = "");
};

}

}

template<typename T, typename... Args>
static void throwException(const QString &_msg, T _value, Args... arguments)
{
    return throwException(_msg.arg(_value), arguments...);
}

void HELPERLIBRARY_EXPORT throwException(const QString &_msg);

