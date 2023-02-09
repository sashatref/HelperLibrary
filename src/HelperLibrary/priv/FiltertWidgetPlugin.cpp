#include "FiltertWidgetPlugin.h"
#include "../Widgets/FilterWidget/filterwidget.h"

namespace HelperLibraryNS
{

FilterWidgetPlugin::FilterWidgetPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void FilterWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool FilterWidgetPlugin::isInitialized() const
{
    return initialized;
}

QWidget *FilterWidgetPlugin::createWidget(QWidget *parent)
{
    FilterWidget *widget = new FilterWidget(parent);
    return widget;
}

QString FilterWidgetPlugin::name() const
{
    return "HelperLibraryNS::FilterWidget";
}

QString FilterWidgetPlugin::group() const
{
    return "HelperLibrary_widgets";
}

QIcon FilterWidgetPlugin::icon() const
{
    return QIcon();
}

QString FilterWidgetPlugin::toolTip() const
{
    return "";
}

QString FilterWidgetPlugin::whatsThis() const
{
    return "";
}

bool FilterWidgetPlugin::isContainer() const
{
    return false;
}

QString FilterWidgetPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"HelperLibraryNS::FilterWidget\" name=\"filterWidget\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>200</width>\n"
           "    <height>40</height>\n"
           "   </rect>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString FilterWidgetPlugin::includeFile() const
{
    return "HelperLibrary/Widgets/FilterWidget/filterwidget.h";
}

}
