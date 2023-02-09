#include "preloadplugininfo.h"
#include "../anymacro.h"

namespace HelperLibraryNS
{

void PreloadPluginInfo::registerType()
{
    GadgetHelper::registerToIGadgetConverter<PreloadPluginInfo>();
}

}


PS_REGISTER_CONSTRUCTOR_FUNC(&HelperLibraryNS::PreloadPluginInfo::registerType)
