#pragma once

#include <QObject>

#include "../igadget.h"
#include "iplugincreator.h"

namespace HelperLibraryNS
{

class IPluginCreator;
class PreloadPluginInfo : public IGadget
{
    Q_GADGET
    DEFINE_MO
    Q_PROPERTY(QString fileName MEMBER fileName)
    Q_PROPERTY(QString pluginName MEMBER pluginName)
    Q_PROPERTY(QString description MEMBER description)
    Q_PROPERTY(bool loaded MEMBER loaded)
    Q_PROPERTY(bool isStatic MEMBER isStatic)
    Q_PROPERTY(QString className MEMBER className)

public:
    QString fileName;
    QString pluginName;
    QString description;
    bool loaded = false;
    IPluginCreator *creator = nullptr;
    bool isStatic = false;
    QString className;

    static void registerType();
};

}

Q_DECLARE_METATYPE(HelperLibraryNS::PreloadPluginInfo)


