#include "plugincollection.h"
#include "ExtListPlugin.h"
#include "PresetListPlugin.h"
#include "ComplexTextEditorPlugin.h"
#include "presetcontrollerplugin.h"
#include "searchlineeditplugin.h"
#include "FiltertWidgetPlugin.h"
#include "LanguageComboPlugin.h"
#include "VariantMapEditorPlugin.h"

PluginsCollection::PluginsCollection(QObject*)
{
    widgets
            << new HelperLibraryNS::ExtListPLugin(this)
            << new HelperLibraryNS::VariantMapEditorPlugin(this)
            << new HelperLibraryNS::PresetListPlugin(this)
            << new HelperLibraryNS::ComplexTextEditorPlugin(this)
            << new HelperLibraryNS::PresetControllerPlugin(this)
            << new HelperLibraryNS::SearchLineEditPLugin(this)
            << new HelperLibraryNS::FilterWidgetPlugin(this)
            << new HelperLibraryNS::LanguageComboPlugin(this);
}

QList<QDesignerCustomWidgetInterface *> PluginsCollection::customWidgets() const
{
    return widgets;
}
