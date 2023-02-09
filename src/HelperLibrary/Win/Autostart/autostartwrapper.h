#pragma once

#include "../../export.h"

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT AutoStartWrapper
{
public:
    AutoStartWrapper(const QString &_appName, const QStringList &_args);

    void setAppName(const QString &_appName);
    void setArgs(const QStringList &_args);

    QString getAutoStartParam() const;

    bool checkForAutoStart() const;

    void setAutoStart(bool _enable);

private:
    static QString regEditPath();

    QString m_appName;
    QStringList m_args;
};

}

