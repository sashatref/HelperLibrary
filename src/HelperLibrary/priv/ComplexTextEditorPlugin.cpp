#include "ComplexTextEditorPlugin.h"
#include "../Widgets/Text/complextexteditor.h"

namespace HelperLibraryNS
{

ComplexTextEditorPlugin::ComplexTextEditorPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void ComplexTextEditorPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool ComplexTextEditorPlugin::isInitialized() const
{
    return initialized;
}

QWidget *ComplexTextEditorPlugin::createWidget(QWidget *parent)
{
    return new ComplexTextEditor(parent);
}

QString ComplexTextEditorPlugin::name() const
{
    return "HelperLibraryNS::ComplexTextEditor";
}

QString ComplexTextEditorPlugin::group() const
{
    return "HelperLibrary_widgets";
}

QIcon ComplexTextEditorPlugin::icon() const
{
    return QIcon();
}

QString ComplexTextEditorPlugin::toolTip() const
{
    return "";
}

QString ComplexTextEditorPlugin::whatsThis() const
{
    return "";
}

bool ComplexTextEditorPlugin::isContainer() const
{
    return false;
}

QString ComplexTextEditorPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"HelperLibraryNS::ComplexTextEditor\" name=\"complexTextEditor\">\n"
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

QString ComplexTextEditorPlugin::includeFile() const
{
    return "HelperLibrary/Widgets/Text/complextexteditor.h";
}

}
