#include "project_pch.h"
#include "serializerexception.h"

namespace SerializerQt
{

BaseException::BaseException(const QString &_text) :
    std::runtime_error(_text.toStdString())
{
}


ToObjectException::ToObjectException(const char *_typeName) :
    BaseException(
        QString(
            "You must register \"%1\" to \"QObject*\" converter before using this function.\n"
            "Invoke this code at start of programm:\n"
            "QMetaType::registerConverter<%1, QObject*>([](const %1 &_value)\n"
            "{\n"
            "    return const_cast<%1*>(&_value);\n"
            "});\n"
            "or \"registerToQObjectConverter<%1>()\" from function.h"
            )
        .arg(_typeName)
        )
{

}


}
