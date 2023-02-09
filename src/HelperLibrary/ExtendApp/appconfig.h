#pragma once

#include "../igadget.h"
#include "../setgetMacro.h"
#include "uilanginfo.h"

#include "../export.h"



namespace HelperLibrary
{

class HELPERLIBRARY_EXPORT AppConfig : public IGadget
{
    Q_GADGET
public:
    buildPropertyP(QList<HelperLibrary::UILangInfo>, uiLangList)
    buildPropertyP(QString, localeName)
    buildPropertyD(bool, useSystemLocale, true)
    buildPropertyD(bool, useProgramLocale, true)
    buildPropertyP(QVariantMap, customProps)

    AppConfig();

    static void registerType();
    virtual const QMetaObject *getMetaObject() const override;
};

HELPERLIBRARY_EXPORT QDebug operator<<(QDebug _debug, const AppConfig &_value);

}

Q_DECLARE_METATYPE(HelperLibrary::AppConfig)

