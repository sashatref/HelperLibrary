#include "presetcontrollerplugin.h"
#include "Widgets/PresetController/presetcontrollerform.h"

namespace HelperLibraryNS
{

PresetControllerPlugin::PresetControllerPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void PresetControllerPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool PresetControllerPlugin::isInitialized() const
{
    return initialized;
}

QWidget *PresetControllerPlugin::createWidget(QWidget *parent)
{
    PresetControllerForm *widget = new PresetControllerForm(parent);
    return widget;
}

QString PresetControllerPlugin::name() const
{
    return "HelperLibraryNS::PresetControllerForm";
}

QString PresetControllerPlugin::group() const
{
    return "HelperLibrary_widgets";
}

QIcon PresetControllerPlugin::icon() const
{
    return QIcon();
}

QString PresetControllerPlugin::toolTip() const
{
    return "";
}

QString PresetControllerPlugin::whatsThis() const
{
    return "";
}

bool PresetControllerPlugin::isContainer() const
{
    return false;
}

QString PresetControllerPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"HelperLibraryNS::PresetControllerForm\" name=\"presetControllerForm\">\n"
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

QString PresetControllerPlugin::includeFile() const
{
    return "HelperLibrary/Widgets/PresetController/presetcontrollerform.h";
}

}
