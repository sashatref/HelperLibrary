#include "appsettings.h"
#include "anymacro.h"
#include "setgetMacro.h"

void HelperLibraryNS::AppSettings::registerType()
{
    GadgetHelper::registerToIGadgetConverter<AppSettings>();
}
