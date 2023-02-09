#include "SecurityPluginManager.h"
#include "ISecurityPlugin.h"

namespace HelperLibraryNS
{

bool SecurityPluginManager::castPlugin(AbstractPlugin *_plugin)
{
    return qobject_cast<ISecurityPlugin*>(_plugin);
}

void SecurityPluginManager::connectPlugin(AbstractPlugin *_plugin)
{
    Q_UNUSED(_plugin);
}

}
