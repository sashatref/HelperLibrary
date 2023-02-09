#include "pluginliststate.h"
#include "../anymacro.h"
#include "../helperscontainter.h"
#include "../converterfunctions.h"

PS_REGISTER_CONSTRUCTOR_FUNC([]
{
    Converters::registerVariantMapToQStringBoolMapConverter();
    qRegisterMetaType<HelperLibraryNS::PluginEnableMap>("HelperLibraryNS::PluginEnableMap");
})
