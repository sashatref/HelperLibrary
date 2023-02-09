#pragma once

#include "../PluginHelper/abstractplugin.h"

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT ISecurityPlugin : public AbstractPlugin
{
    Q_OBJECT
public:
    virtual void setConfig(const QVariant &_v) = 0;
    virtual void makeCheck() = 0;

    virtual QString getName() const override;
    virtual QString getVersion() const override;
    virtual QString getDescription() const override;
    virtual void turnOn() override;
    virtual void turnOff() override;
};


}
