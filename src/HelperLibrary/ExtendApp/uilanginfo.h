#pragma once


#include "../igadget.h"
#include "../setgetMacro.h"
#include "../export.h"

namespace HelperLibrary
{

class HELPERLIBRARY_EXPORT UILangInfo : public IGadget
{
    Q_GADGET
public:
    buildPropertyP(QString, fullName)
    buildPropertyP(QString, shortName)
    buildPropertyP(QString, iconPath)

    UILangInfo(const QString &_fullName = "",
               const QString &_shortName = "",
               const QString &_iconPath = "");

    static void registerType();

    virtual const QMetaObject *getMetaObject() const override;
};

QDebug HELPERLIBRARY_EXPORT operator<<(QDebug _debug, const UILangInfo &_value);

}

Q_DECLARE_METATYPE(HelperLibrary::UILangInfo)

