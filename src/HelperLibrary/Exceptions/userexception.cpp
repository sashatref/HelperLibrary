#include "../project_pch.h"
#include "userexception.h"

#ifdef _MSC_VER
    #include "customstackwalker.h"
#endif

namespace HelperLibrary
{

namespace UserExceptions
{
    BaseException::BaseException(const QString &_text, bool _stackTrace):
        std::runtime_error(_text.toStdString())
    {
#ifdef _MSC_VER
        if(_stackTrace)
        {
            CustomStackWalker sw;
            sw.ShowCallstack();
            m_stackTrace = sw.getTraceList();

        }
#else
        Q_UNUSED(_stackTrace);
#endif
    }

    QStringList BaseException::getStackTraceList() const
    {
        return m_stackTrace;
    }

    QString BaseException::getText() const
    {
        return what();
    }

    QDebug operator<<(QDebug d, const BaseException &e)
    {
        d.nospace();
        d << e.getText();
        if(e.getStackTraceList().size())
        {
            d << "\n\t";
        }

        d << e.getStackTraceList().join("\n\t").toStdString().c_str();
        return d;
    }

    ToObjectException::ToObjectException(const char *_typeName) :
        BaseException(
            QString(
                "You must register \"%1\" to \"QObject*\" converter before using this function.\n"
                )
            .arg(_typeName)
            )
    {

    }

    ToIGadgetException::ToIGadgetException(const char *_typeName) :
        BaseException(
            QString(
                "You must register \"%1\" to \"IGadget*\" converter before using this function.\n"
                )
            .arg(_typeName)
            )
    {

    }

    NotImplementedException::NotImplementedException(const QString &_text):
        BaseException(_text)
    {

    }

}

}



void throwException(const QString &_msg)
{
    throw HelperLibrary::UserExceptions::BaseException(_msg, false);
}

