#pragma once

#include "../IGadget/igadget.h"
#include "../setgetMacro.h"
#include "../export.h"

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT AppSettings : public IGadget
{
    Q_GADGET
    DEFINE_MO
public:
    buildPropertyD(QString, settingsPath, "settings.xml")
    buildPropertyD(QString, layoutPath, "layout.bin")
    buildPropertyD(QString, appConfigPath, "appConfig.xml")

    static void registerType();
};

}

Q_DECLARE_METATYPE(HelperLibraryNS::AppSettings)

