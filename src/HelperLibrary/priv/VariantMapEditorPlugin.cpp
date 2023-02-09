#include "VariantMapEditorPlugin.h"
#include "Widgets/VariantMapEditor/variantmapeditor.h"

namespace HelperLibraryNS
{

VariantMapEditorPlugin::VariantMapEditorPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void VariantMapEditorPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool VariantMapEditorPlugin::isInitialized() const
{
    return initialized;
}

QWidget *VariantMapEditorPlugin::createWidget(QWidget *parent)
{
    VariantMapEditor *widget = new VariantMapEditor(parent);
    return widget;
}

QString VariantMapEditorPlugin::name() const
{
    return "HelperLibraryNS::VarianMapEditor";
}

QString VariantMapEditorPlugin::group() const
{
    return "HelperLibrary_widgets";
}

QIcon VariantMapEditorPlugin::icon() const
{
    return QIcon();
}

QString VariantMapEditorPlugin::toolTip() const
{
    return "";
}

QString VariantMapEditorPlugin::whatsThis() const
{
    return "";
}

bool VariantMapEditorPlugin::isContainer() const
{
    return false;
}

QString VariantMapEditorPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"HelperLibraryNS::VarianMapEditor\" name=\"variantMapEditor\">\n"
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

QString VariantMapEditorPlugin::includeFile() const
{
    return "HelperLibrary/Widgets/VariantMapEditor/VariantMapEditor.h";
}

}
