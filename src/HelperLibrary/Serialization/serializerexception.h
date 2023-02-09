#pragma once

#include <exception>
#include <stdexcept>
#include <QString>
#include "export.h"

namespace SerializerQt
{

class HELPERLIBRARY_EXPORT  BaseException : public std::runtime_error
{
public:
    BaseException(const QString &_text = "");
};

class HELPERLIBRARY_EXPORT ToObjectException : public BaseException
{
public:
    ToObjectException(const char *_typeName);
};

}
