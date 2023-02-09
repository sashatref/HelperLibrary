#include "ExtListPlugin.h"
#include "../Widgets/ListWidgets/extlist.h"

namespace HelperLibraryNS
{

ExtListPLugin::ExtListPLugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void ExtListPLugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool ExtListPLugin::isInitialized() const
{
    return initialized;
}

QWidget *ExtListPLugin::createWidget(QWidget *parent)
{
    ExtList *widget = new ExtList(parent);
    return widget;
}

QString ExtListPLugin::name() const
{
    return "HelperLibraryNS::ExtList";
}

QString ExtListPLugin::group() const
{
    return "HelperLibrary_widgets";
}

QIcon ExtListPLugin::icon() const
{
    return QIcon();
}

QString ExtListPLugin::toolTip() const
{
    return "";
}

QString ExtListPLugin::whatsThis() const
{
    return "";
}

bool ExtListPLugin::isContainer() const
{
    return false;
}

QString ExtListPLugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"HelperLibraryNS::ExtList\" name=\"extList\">\n"
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

QString ExtListPLugin::includeFile() const
{
    return "HelperLibrary/Widgets/ListWidgets/extlist.h";
}

}
