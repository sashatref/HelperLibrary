#include "PresetListPlugin.h"
#include "../Widgets/ListWidgets/presetslist.h"

namespace HelperLibraryNS
{

PresetListPlugin::PresetListPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void PresetListPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool PresetListPlugin::isInitialized() const
{
    return initialized;
}

QWidget *PresetListPlugin::createWidget(QWidget *parent)
{
    PresetsList *widget = new PresetsList(parent);
    return widget;
}

QString PresetListPlugin::name() const
{
    return "HelperLibraryNS::PresetsList";
}

QString PresetListPlugin::group() const
{
    return "HelperLibrary_widgets";
}

QIcon PresetListPlugin::icon() const
{
    return QIcon();
}

QString PresetListPlugin::toolTip() const
{
    return "";
}

QString PresetListPlugin::whatsThis() const
{
    return "";
}

bool PresetListPlugin::isContainer() const
{
    return false;
}

QString PresetListPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"HelperLibraryNS::PresetsList\" name=\"presetsList\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>200</width>\n"
           "    <height>300</height>\n"
           "   </rect>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString PresetListPlugin::includeFile() const
{
    return "HelperLibrary/Widgets/ListWidgets/presetslist.h";
}

}
