#pragma once

#include "../PluginHelper/baseplugincreatormanager.h"

namespace HelperLibraryNS
{

class SecurityPluginManager : public BasePluginCreatorManager
{
public:


protected:
    virtual bool castPlugin(AbstractPlugin *_plugin) override;
    virtual void connectPlugin(AbstractPlugin *_plugin) override;
};

}
